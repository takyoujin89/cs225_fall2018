/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>
#include <cmath>
using namespace std;

//checks if first<second at given dimension
template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    /**
     * @todo Implement this function!
     */
     bool ret = false;
     if(first[curDim]<second[curDim]){ //if less than then true!
       ret = true;
     }
     if(first[curDim]==second[curDim]){ //if equal then also true!
       if(first<second){
         ret = true;
       }
     }

    return ret;
}
//checks if potential is a smaller distance away from target
template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */
     int dim = Dim; //dimnsion of compared points
     double d1 = 0; // distance of currentBest
     double d2 = 0; // distance of potential
     bool ret = false;
     for (int i = 0; i< dim; i++){
       double x = currentBest[i] - target[i];
       x = x*x;
       double y = potential[i] - target[i];
       y = y*y;
       d1+=x;
       d2+=y;
     }
     if(d2<d1){
       ret = true;
     }
     if(d2==d1){
       if(potential<currentBest){
         ret = true;
       }
     }
     return ret;
}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */
}

template <int Dim>
KDTree<Dim>::KDTree(const KDTree<Dim>& other) {
  /**
   * @todo Implement this function!
   */
}

template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree<Dim>& rhs) {
  /**
   * @todo Implement this function!
   */

  return *this;
}

template <int Dim>
KDTree<Dim>::~KDTree() {
  /**
   * @todo Implement this function!
   */
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */

    return Point<Dim>();
}
