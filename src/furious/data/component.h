

#ifndef _FURIOUS_COMPONENT_H_
#define _FURIOUS_COMPONENT_H_

#include <common/platform.h>
#include <data/datatypes.h>
#include <string>
#include <vector>

namespace furious {
  namespace data {

#define COMPONENT_IDENTIFIER(fieldname) \
    template<typename Q_T> \
    struct fieldname { \
      Q_T fieldname; \
      using Q_type = Q_T; \
      constexpr static char const *Q_name() { return #fieldname; } \
      Q_T &Q_value() & { return fieldname; } \
      Q_T const &Q_value() const & { return fieldname; } \
      Q_T &&Q_value() && { return fieldname; } \
    };

    template<typename...Fields>
      struct Component : public Fields... {
        using component_type = Component;

        Component() = default;
        Component(Component const &) = default;
        constexpr Component(typename Fields::Q_type &&...x)
          : Fields{x}... {}

        // FIXME relies on undefined behavior, can't be constexpr
        template<typename Field>
          /*constexpr*/ static std::uintptr_t offset_of() {
            return reinterpret_cast<std::uintptr_t>(&static_cast<Component*>(nullptr)->Field::Q_value());
          }

        template<typename Field>
          constexpr static std::size_t size_of() { return sizeof(typename Field::Q_type); }

        template<typename Field>
          constexpr static char_t const *name_of() { return Field::Q_name(); }


        template<template<typename T> class Trait, typename Function>
          static void each_field(Function &&f)
          {
            char_t __attribute__((unused)) discard[] = {(
                f(Fields::Q_name(), offset_of<Fields>(), size_of<Fields>(),
                  Trait<typename Fields::Q_type>::value())
                , '\0')...};
          }

        template<typename Function>
          auto apply(Function &&f) & -> decltype(f(this->Fields::Q_value()...))
          { return f(this->Fields::Q_value()...); }
        template<typename Function>
          auto apply(Function &&f) const & -> decltype(f(this->Fields::Q_value()...))
          { return f(this->Fields::Q_value()...); }
        template<typename Function>
          auto apply(Function &&f) && -> decltype(f(this->Fields::Q_value()...))
          { return f(this->Fields::Q_value()...); }
      };
  }
}
#endif
