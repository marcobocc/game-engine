#ifndef H_HETEROGENEOUS_MAP
#define H_HETEROGENEOUS_MAP

#include <tuple>
#include <unordered_map>
#include <utility>

namespace util {
	template<typename KeyType, typename... Ts>
	class heterogeneous_map {
	public:
		template<typename T>
		decltype(auto) begin() noexcept {
			return get_container<T>().begin();
		}

		template<typename T>
		decltype(auto) begin() const noexcept {
			return get_container<T>().begin();
		}

		template<typename T>
		decltype(auto) cbegin() const noexcept {
			return get_container<T>().cbegin();
		}

		template<typename T>
		decltype(auto) end() noexcept {
			return get_container<T>().end();
		}

		template<typename T>
		decltype(auto) end() const noexcept {
			return get_container<T>().end();
		}

		template<typename T>
		decltype(auto) cend() const noexcept {
			return get_container<T>().cend();
		}

		template<typename T>
		decltype(auto) empty() const noexcept {
			return get_container<T>().empty();
		}

		template<typename T>
		decltype(auto) size() const noexcept {
			return get_container<T>().size();
		}

		template<typename T, typename... Args>
		decltype(auto) try_emplace(const KeyType& key, Args&&... args) {
			return get_container<T>().try_emplace(key, std::forward<Args>(args)...);
		}

		template<typename T>
		void erase(const KeyType& key) const {
			get_container<T>().erase(key);
		}

		template<typename T>
		void clear() const {
			get_container<T>().clear();
		}

		template<typename T>
		decltype(auto) find(const KeyType& key) const {
			return get_container<T>().find(key);
		}

	protected:
		template<typename T>
		std::unordered_map<KeyType, T>& get_container() {
			static_assert(std::disjunction_v<std::is_same<T, Ts>...>,
				"heterogenous_map is not storing objects of this type");
			return std::get<std::unordered_map<KeyType, T>>(m_containers);
		}

		template<typename T>
		const std::unordered_map<KeyType, T>& get_container() const {
			static_assert(std::disjunction_v<std::is_same<T, Ts>...>,
				"heterogenous_map is not storing objects of this type");
			return std::get<std::unordered_map<KeyType, T>>(m_containers);
		}

	private:
		std::tuple<std::unordered_map<KeyType, Ts>...> m_containers;
	};
};

#endif