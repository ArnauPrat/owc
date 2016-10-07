
#ifndef _FURIOUS_COMPONENT_H_
#define _FURIOUS_COMPONENT_H_

#include "irow.h"

namespace furious
{
  namespace data
  {

#define FIELD_IDENTIFIER(fieldname) \
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
      struct Component : IRow, Fields... {
        using component_type = Component;
        Component() = default;
        Component(Component const &) = default;
        constexpr Component(typename Fields::Q_type &&...x)
          : IRow(), Fields{x}... {}
        ;

        /**
         * Gets the offset of a field in the row in bytes
         */
        // FIXME relies on undefined behavior, can't be constexpr
        template<typename Field>
          /*constexpr*/ static std::uintptr_t offset_of() {
            return reinterpret_cast<std::uintptr_t>(&static_cast<Component*>(nullptr)->Field::Q_value());
          }

        /**
         * Gets the size of a field in the row
         */
        template<typename Field>
          constexpr static std::size_t size_of() { return sizeof(typename Field::Q_type); }

        /**
         * Gets the name of the gien field
         */
        template<typename Field>
          constexpr static char_t const *name_of() { return Field::Q_name(); }

        /**
         * Applies a function to each field of the row
         */
        template<template<typename T> class Trait, typename Function>
          static void each_field(Function &&f)
          {
            char_t __attribute__((unused)) discard[] = {(
                f(Fields::Q_name(), offset_of<Fields>(), size_of<Fields>(),
                  Trait<typename Fields::Q_type>::value())
                ,'\0')...};
          }

        /**
         * Applies a function to the row
         */
        template<typename Function>
          auto apply(Function &&f) & 
          { return f(this->Fields::Q_value()...); }

        /**
         * Applies a function to the row
         */
        template<typename Function>
          auto apply(Function &&f) const & 
          { return f(this->Fields::Q_value()...); }

        /**
         * Applies a function to the row
         */
        template<typename Function>
          auto apply(Function &&f) && 
          { return f(this->Fields::Q_value()...); }

      };

  } /* data */ 

} /* furious */ 
#endif
