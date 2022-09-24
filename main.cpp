#include <cstdint>
#include <string.h>

#include <string>
#include <algorithm>
#include <map>
#include <iostream>
#include <sstream>
#include <mutex>

#include <execinfo.h>


constexpr inline uint64_t fnv1_64(const void* data, size_t nbytes) {
    if (data == nullptr) return 0;
    if (nbytes == 0) {
        nbytes = strlen((char*) data);
    }

    unsigned char* dp;
    uint64_t h = 0xCBF29CE484222325ULL;

    for (dp = (unsigned char*) data; *dp && nbytes > 0; dp++, nbytes--) {
        h *= 0x100000001B3ULL;
        h ^= *dp;
    }
    return h;
}

struct SafeStackTrace {
    inline static const size_t nMaxFrame_      = 128;
    int                        nFrames_        = 0;
    int                        numFramesQuery_ = 0;
    void* callStackPtrs_[nMaxFrame_] = {nullptr};
    SafeStackTrace() { generate(); }
    SafeStackTrace(const SafeStackTrace& lhs) = default;
    SafeStackTrace(SafeStackTrace&& lhs) = default;
    ~SafeStackTrace() = default;
    uint64_t hash() {
        return fnv1_64((const char*)callStackPtrs_, sizeof(void*) * numFramesQuery_);
    }
    void generate() {
        ::memset(callStackPtrs_, 0, sizeof(callStackPtrs_));
        nFrames_        = ::backtrace(callStackPtrs_, nMaxFrame_);
        numFramesQuery_ = std::min(nFrames_, (int)nMaxFrame_);
    }
    std::ostream& print(std::ostream& strm) noexcept {
        if (nFrames_ == 0) { return strm; }
        char** symbols = ::backtrace_symbols(callStackPtrs_, numFramesQuery_);
        if (symbols != nullptr) {
            for (int i = 0; i < numFramesQuery_; i++) {
                strm << symbols[i] << "\n";
            }
        }
        delete symbols;
        return strm;
    }
};

struct ShowPath {
    bool                   noisy_{false};
    bool                   showStackTrace_{true};
    static bool            globalShowStackTrace_;
    mutable SafeStackTrace saveStackTrace_;
    std::string            name_;
    uint64_t               nameId_{0};
    char                   nameIdStr_[32];
    mutable int            numCalls_{0}
    ;
    mutable std::map<uint64_t, int>  uniquePaths_;

    explicit ShowPath(std::string_view name, bool noisyD = false) : name_(name), noisy_(noisyD) {
        nameId_ = fnv1_64(name_.c_str(), name_.size());
        sprintf(nameIdStr_, "0x%lx", nameId_);
    }

    void generate(std::mutex& mtx) const {
        if (globalShowStackTrace_ && showStackTrace_) {
            std::unique_lock<std::mutex>	lock(mtx);
            numCalls_++;
            saveStackTrace_.generate();
            auto hash = saveStackTrace_.hash();
            auto iter = uniquePaths_.find(hash);
            if (iter == uniquePaths_.end()) {
                std::cerr << "ShowPath-BEGIN: " << nameIdStr_ << " -(" << name_ << ")- NumPaths:" << uniquePaths_.size() << " NumCalls:" << numCalls_  << std::endl;
                saveStackTrace_.print(std::cerr);
                std::cerr << "ShowPath-END__: " << nameIdStr_ << " -(" << name_ << ")- NumPaths:"  << std::endl;
            } else {
                iter->second++;
                if (noisy_) {
                    std::cerr << "ShowPath-NOISY: " << nameIdStr_ << " -(" << name_ << ")- NumPaths:" << uniquePaths_.size() << " NumCalls:" << numCalls_  << std::endl;
                }
            }
        }
    }
};

#ifdef REMOVE_SHOWPATH
#  define SHOWPATH(NAME)
#  define SHOWPATH_NOISY(NAME)
#else
#  define SHOWPATH(NAME) { static std::mutex mtx; static ShowPath showPath( NAME ); showPath.generate(mtx); }
#  define SHOWPATH_NOISY(NAME) { static std::mutex mtx; static ShowPath showPath( NAME , true); showPath.generate(mtx); }
#endif

bool ShowPath::globalShowStackTrace_ = true;

#include <iostream>

int main() {
    std::cout << "Hello, World!" << std::endl;
    SHOWPATH(__PRETTY_FUNCTION__);
    return 0;
}
