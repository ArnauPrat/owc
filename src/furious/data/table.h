


#ifndef _FURIOUS_TABLE_H_
#define _FURIOUS_TABLE_H_

#include <vector>
#include <utility>

namespace furious {
  namespace data {
    template<template<typename...Fields> class T> 
      class Table {
        public:

          Table() = default ;
          Table( const Table &  ) = delete;
          Table & operator=( const Table &) = delete;
          Table( Table && ) = delete;
          Table & operator=( Table &&) = delete;

			    void insert( typename Fields::Q_type &&...x) {
            data.emplace_back(std::forward<Fields::Q_type>(x)...);
          }

          void insert( const T & component ) {
            data.push_back(component);
          }

          void insert(T && component) {
            data.push_back(std::forward<T>(component))
          }

        private:
          std::vector<Component> data;

      };
  } /* data */ 
} /* furious */ 
#endif
