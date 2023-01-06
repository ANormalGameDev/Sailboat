#ifndef SAILBOAT_H
#define SAILBOAT_H

#include <array>
#include <tuple>
#include <functional>

namespace Sailboat {
    template <typename ...Ts> class Tween;

    namespace traits {
        template <typename T, typename ...> struct first_t { typedef T type; };
        template <typename T, typename ...Ts> struct homogen { static constexpr bool value {(std::is_same_v<T, Ts> && ...)}; };
        
        template <bool homogen, typename ...Ts> struct values_type {};
        template <typename ...Ts> struct values_type<true, Ts...> { typedef typename std::array<typename first_t<Ts...>::type, sizeof...(Ts)> type; };
        template <typename ...Ts> struct values_type<false, Ts...> { typedef typename std::tuple<Ts...> type; };
    
        template <typename ...Ts> struct tw_traits {
            typedef typename values_type<homogen<Ts...>::value, Ts...>::type value_type;
            typedef std::array<u_int16_t, sizeof...(Ts)> dur_arr_type;
            typedef std::array<int16_t, sizeof...(Ts)> del_arr_type;
            typedef std::function<float(float, float, float)> easing_type;
            typedef std::array<std::function<float(float, float, float)>, sizeof...(Ts)> eas_arr_type;
            typedef Tween<Ts...> type;
        };
    }

    namespace detail {
        template <int ...> struct seq {};
        template <int N, int ...S> struct gen_seq : gen_seq <N - 1, N - 1, S...> {};
        template <int ...S> struct gen_seq <0, S...> : seq<S...> {};

        template <std::size_t I, typename Ar, typename ...Fs> struct tup_helper {
            static void resolve(Ar&, Fs...) { return; }
        };

        template <std::size_t I, typename Ar, typename F, typename ...Fs> struct tup_helper<I, Ar, F, Fs...> {
            static void resolve(Ar& arr, F f, Fs... fs) {
                std::get<I>(arr) = f;
                tup_helper<I + 1, Ar, Fs...>::resolve(arr, fs...);
            }
        };

        template <typename ...Ts> class Point {
            private:
                typedef traits::tw_traits<Ts...> m_traits;
            public:
                typename m_traits::value_type values;
                typename m_traits::del_arr_type delays;
                typename m_traits::dur_arr_type durations;
                typename m_traits::eas_arr_type easings;
                int at {0};

                bool operator > (int i);
                bool operator < (int i);
                Point(Ts... ts);
        };
    }

    template <typename ...Ts> class Tween {
        private:
            typedef traits::tw_traits<Ts...> m_traits;

            typename m_traits::value_type m_values;

            std::vector<detail::Point<Ts...>> m_points;
            std::function<void(Ts...)> on_step_cb {NULL};
            std::size_t m_length {0};
            int m_at {0};
        public:
            inline Tween<Ts...>& to(Ts... ts);

            template <typename I> inline Tween<Ts...>& in(I time);
            template <typename ...Is> Tween<Ts...>& in(Is... is);

            template <typename I> inline Tween<Ts...>& wait(I time);
            template <typename ...Is> Tween<Ts...>& wait(Is... is);

            inline Tween<Ts...>& via(typename m_traits::easing_type&& func);
            template <typename F, typename F1, typename ...Fs> inline Tween<Ts...>& via(F&& f, F1&& f1, Fs&&... fs);

            inline const typename m_traits::value_type step(int by = 1, bool suppress_cb = false);
            inline Tween<Ts...>& on_step(std::function<void(Ts...)>&& func);

            inline const typename m_traits::value_type seek(std::size_t at);
            inline std::size_t length();
            inline std::size_t at();

            Tween(Ts... ts);

            // Functions for user convenience
            inline Tween<Ts...>& jump(std::size_t by);
            inline Tween<Ts...>& jump_to_end();
            inline Tween<Ts...>& jump_to_start();
    };

    template <typename ...Ts> static inline typename traits::tw_traits<Ts...>::type from(Ts... ts) {
        return typename traits::tw_traits<Ts...>::type(ts...);
    }

    namespace Easing {
        static inline float Lerp(float from, float to, float x) { return from + (to - from) * x; }
        static inline float SmoothStep(float from, float to, float x) { return from + (to - from) * x * x * (3 - 2 * x); }
    }
}

#include "Sailboat.tci"

#endif