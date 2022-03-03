#include "p2.h"

#ifndef MAX_INT
#define MAX_INT (((unsigned int)(-1)) >> 1)
#endif

//************************************************************
//*********                                     **************
//*********                List                 **************
//*********                                     **************
//************************************************************

int accumulate(list_t list, int (*fn)(int, int), int base) {
  return list_isEmpty(list)
             ? base
             : fn(list_first(list), accumulate(list_rest(list), fn, base));
}
/*
// REQUIRES: "fn" must be associative.
//
// EFFECTS: Returns "base" if "list" is empty.
//          Returns fn(list_first(list), 
//                      accumulate(list_rest(list), fn, base) otherwise.
//
// For example, if you have the following function:
//
//           int add(int x, int y);
//
// Then the following invocation returns the sum of all elements:
//
//           accumulate(list, add, 0);
*/ 



int size(list_t list) {
  return list_isEmpty(list) ? 0 : size(list_rest(list)) + 1;
}
/* 
// EFFECTS: Returns the number of elements in "list".
//          Returns zero if "list" is empty.
*/ 



int sum(list_t list) {
  return list_isEmpty(list) ? 0 : sum(list_rest(list)) + list_first(list);
}

// static int sum_helper(int a, int b){
//     return a+b;
// }

// int sum(list_t list) {
//   return accumulate(list,sum_helper,0) ;
// }



int product(list_t list) {
  return list_isEmpty(list) ? 1 : product(list_rest(list)) * list_first(list);
}

// static int product_helper(int a, int b){
//     return a*b;
// }

// int product(list_t list) {
//   return accumulate(list,product_helper,1);
// }



list_t reverse(list_t list) {
  return list_isEmpty(list) ? list_make()
                            : append(reverse(list_rest(list)),
                                     list_make(list_first(list), list_make()));
}
/*
// EFFECTS: Returns the reverse of "list".
//
// For example: the reverse of ( 3 2 1 ) is ( 1 2 3 )
*/



list_t append(list_t first, list_t second) {
  return list_isEmpty(first)
             ? second
             : list_make(list_first(first), append(list_rest(first), second));
}
/*
// EFFECTS: Returns the list (first second).
//
// For example: append(( 2 4 6 ), ( 1 3 )) gives
// the list ( 2 4 6 1 3 ).
*/ 



static bool filter_odd_helper(int n) { return n % 2 != 0; }
//a function to help filter_odd to recur

list_t filter_odd(list_t list) { return filter(list, filter_odd_helper); }
/*
// EFFECTS: Returns a new list containing only the elements of the
//          original "list" which are odd in value, 
//          in the order in which they appeared in list.
//
// For example, if you apply filter_odd to the list ( 3 4 1 5 6 ),
// you would get the list ( 3 1 5 ).
*/


static bool filter_even_helper(int n) { return n % 2 == 0; }
//a function to help filter_even to recur

list_t filter_even(list_t list) { return filter(list, filter_even_helper); }
/*
// EFFECTS: Returns a new list containing only the elements of the
//          original "list" which are even in value, 
//          in the order in which they appeared in list.
*/




list_t filter(list_t list, bool (*fn)(int)) {
  if (list_isEmpty(list) == true) return list_make();
  if (fn(list_first(list)) == true) {
    return list_make(list_first(list), filter(list_rest(list), fn));
  } else
    return filter(list_rest(list), fn);
}
/*
// EFFECTS: Returns a list containing precisely the elements of "list"
//          for which the predicate fn() evaluates to true, in the
//          order in which they appeared in list.
//
// For example, if predicate bool odd(int a) returns true if a is odd,
// then the function filter(list, odd) has the same behavior as the
// function filter_odd(list).
*/




list_t insert_list(list_t first, list_t second, unsigned int n) {
  return append(append(chop(first, size(first) - n), second),
                reverse(chop(reverse(first), n)));
}
/*
// REQUIRES: n <= the number of elements in "first".
//
// EFFECTS: Returns a list comprising the first n elements of
//          "first", followed by all elements of "second",
//           followed by any remaining elements of "first".
//
//     For example: insert (( 1 2 3 ), ( 4 5 6 ), 2)
//            gives ( 1 2 4 5 6 3 ).
*/


list_t chop(list_t list, unsigned int n) {
  if (n > 0)
    return reverse(list_rest(reverse(chop(list, n - 1))));
  else
    return list;
}
/*
// REQUIRES: "list" has at least n elements.
//
// EFFECTS: Returns the list equal to "list" without its last n
//          elements.
*/



//************************************************************
//*********                                     **************
//*********            BINARY TREE              **************
//*********                                     **************
//************************************************************

int tree_sum(tree_t tree) {
  return tree_isEmpty(tree) ? 0
                            : (tree_elt(tree) + tree_sum(tree_left(tree)) +
                               tree_sum(tree_right(tree)));
}
/*
// EFFECTS: Returns the sum of all elements in "tree". 
//          Returns zero if "tree" is empty.
*/



bool tree_search(tree_t tree, int key) {
  return tree_isEmpty(tree)
             ? 0
             : (tree_elt(tree) == key) || tree_search(tree_left(tree), key) ||
                   tree_search(tree_right(tree), key);
}
/*
// EFFECTS: Returns true if there exists any element in "tree"
//          whose value is "key". Otherwise, return "false".
*/



int depth(tree_t tree) {
  return tree_isEmpty(tree)
             ? 0
             : ((depth(tree_left(tree)) > depth(tree_right(tree)))
                    ? depth(tree_left(tree)) + 1
                    : depth(tree_right(tree))) +
                   1;
}
/* 
// EFFECTS: Returns the elements of "tree" in a list using an
//          in-order traversal. An in-order traversal prints 
//          the "left most" element first, then the second-left-most, 
//          and so on, until the right-most element is printed.
//
//          For any node, all the elements of its left subtree
//          are considered as on the left of that node and
//          all the elements of its right subtree are considered as
//          on the right of that node.
*/



int tree_min(tree_t tree) {
  // if (tree_isEmpty(tree) == true)
  //     return 0;
  // if it is necessary
  //if (tree_isEmpty(tree) == true) return 0;
  if (tree_isEmpty(tree)) return MAX_INT;
  if (tree_elt(tree) < tree_min(tree_left(tree)))
    return (tree_elt(tree) < tree_min(tree_right(tree)))
               ? tree_elt(tree)
               : tree_min(tree_right(tree));
  else
    return (tree_min(tree_left(tree)) < tree_min(tree_right(tree)))
               ? tree_min(tree_left(tree))
               : tree_min(tree_right(tree));
}
/*
// REQUIRES: "tree" is non-empty.
// EFFECTS: Returns the smallest element in "tree".
*/



list_t traversal(tree_t tree) {
  return tree_isEmpty(tree)
             ? list_make()
             : append(traversal(tree_left(tree)),
                      list_make(tree_elt(tree), traversal(tree_right(tree))));
}
/*
// EFFECTS: Returns the elements of "tree" in a list using an
//          in-order traversal. An in-order traversal prints 
//          the "left most" element first, then the second-left-most, 
//          and so on, until the right-most element is printed.
//
//          For any node, all the elements of its left subtree
//          are considered as on the left of that node and
//          all the elements of its right subtree are considered as
//          on the right of that node.
*/


bool tree_hasPathSum(tree_t tree, int sum) {
  if (tree_isEmpty(tree)) return false;
  if (((tree_elt(tree) == sum)) && (tree_isEmpty(tree_left(tree))) &&
      (tree_isEmpty(tree_right(tree))))
    return true;
  else
    return tree_hasPathSum(tree_left(tree), sum - tree_elt(tree)) ||
           tree_hasPathSum(tree_right(tree), sum - tree_elt(tree));
}
/* 
// EFFECTS: Returns true if and only if "tree" has at least one root-to-leaf
//          path such that adding all elements along the path equals "sum".
//          
*/


bool covered_by(tree_t A, tree_t B) {
  if (tree_isEmpty(A)) return true;
  if (tree_isEmpty(B))
    return false;
  else
    return (tree_elt(A) == tree_elt(B) &&
            covered_by(tree_left(A), tree_left(B)) &&
            covered_by(tree_right(A), tree_right(B)));
}
/*
// EFFECTS: Returns true if tree A is covered by tree B.
*/     



bool contained_by(tree_t A, tree_t B) {
  if (tree_isEmpty(B)) {
    return false;
  }
  if (covered_by(A, B))
    return true;
  else
    return (contained_by(A, tree_left(B)) || contained_by(A, tree_right(B)));
}
/*
// EFFECTS: Returns true if tree A is covered by tree B
//          or a subtree of B.
*/ 


tree_t insert_tree(int elt, tree_t tree) {
  if (tree_isEmpty(tree)) return tree_make(elt, tree_make(), tree_make());
  if (elt < tree_elt(tree))
    return tree_make(tree_elt(tree), insert_tree(elt, tree_left(tree)),
                     tree_right(tree));
  else
    return tree_make(tree_elt(tree), tree_left(tree),
                     insert_tree(elt, tree_right(tree)));
}
/* 
// REQUIRES: "tree" is a sorted binary tree.
//
// EFFECTS: Returns a new tree with elt inserted at a leaf such that 
//          the resulting tree is also a sorted binary tree.
//
*/