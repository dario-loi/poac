#ifndef GIT2_REV_LIST_HPP
#define GIT2_REV_LIST_HPP

#include <memory>
#include <string>
#include <git2/oid.h>
#include <poac/util/git2-cpp/global.hpp>
#include <poac/util/git2-cpp/exception.hpp>

namespace git2 {
    struct oid {
        git_oid raw;

        /// Parse a hex-formatted object id into an oid structure.
        oid(const std::string& str) {
            git2::init();
            git2_throw(git_oid_fromstrn(&this->raw, str.c_str(), str.size()));
        }

        /// Parse a hex-formatted object id into an oid structure.
        oid(const std::unique_ptr<unsigned char>& bytes) {
            git2::init();
            git_oid_fromraw(&this->raw, bytes.get());
        }

        oid() = delete;
        ~oid() = default;

        oid(const oid&) = delete;
        oid& operator=(const oid&) = delete;
        oid(oid&&) = default;
        oid& operator=(oid&&) = default;

        /// Test if this OID is all zeros.
        bool is_zero() const {
            return git_oid_iszero(&raw) == 1;
        }

        friend std::ostream& operator<<(std::ostream& os, const oid& o) {
            std::unique_ptr<char> s(git_oid_tostr_s(&o.raw));
            os << *s;
            return os;
        }
    };

    bool operator==(const oid& lhs, const oid& rhs) {
        return git_oid_equal(&lhs.raw, &rhs.raw) != 0;
    }
} // end namespace git2

#endif	// !GIT2_REV_LIST_HPP
