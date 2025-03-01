module;

// external
#include <boost/functional/hash.hpp>

export module poac.core.resolver.registry;

import poac.util.result;
import poac.util.rustify;

export namespace poac::core::resolver::registry {

// NOLINTNEXTLINE(bugprone-exception-escape)
struct Registry {
  String index;
  String type;
};

inline auto operator==(const Registry& lhs, const Registry& rhs) -> bool {
  return lhs.index == rhs.index && lhs.type == rhs.type;
}

inline auto hash_value(const Registry& r) -> usize {
  usize seed = 0;
  boost::hash_combine(seed, r.index);
  boost::hash_combine(seed, r.type);
  return seed;
}

using Registries = HashMap<String, Registry>;

} // namespace poac::core::resolver::registry
