#ifndef H_BASEMANAGER
#define H_BASEMANAGER

#include "util/heterogeneous_map.h"
#include <memory>
#include <utility>

template<typename KeyType, typename... Ts>
class BaseManager {
public:
	template<typename T, typename... Args>
	decltype(auto) try_alloc(const KeyType& key, Args&&... args) {
		auto [it, insert_successful] = m_containers.try_emplace<std::unique_ptr<T>>(key, nullptr);
		if (insert_successful) {
			it->second = std::make_unique<T>(std::forward<Args>(args)...);
		}
		return std::make_pair(it, insert_successful);
	}

	template<typename T>
	void dealloc(const KeyType& key) {
		m_containers.erase<std::unique_ptr<T>>(key);
	}

	template<typename T>
	decltype(auto) find(const KeyType& key) const {
		return m_containers.find<std::unique_ptr<T>>(key);
	}

	template <typename T>
	decltype(auto) cbegin() const noexcept {
		return m_containers.cbegin<std::unique_ptr<T>>();
	}

	template <typename T>
	decltype(auto) cend() const noexcept {
		return m_containers.cend<std::unique_ptr<T>>();
	}

protected:
	util::heterogeneous_map<KeyType, std::unique_ptr<Ts>...> m_containers;
};

#endif