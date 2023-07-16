#include "chain.h"
#include <cmath>
#include <iostream>


// PA1 functions

/**
 * Destroys the current Chain. This function should ensure that
 * memory does not leak on destruction of a chain.
 */
Chain::~Chain() {
  /* your code here */
  clear();
}

/**
 * Inserts a new node after the node pointed to by p in the
 * chain (so p->next is the new node) and returns a pointer to
 * the newly created node.
 * If p is NULL, inserts a new head node to the chain.
 * This function **SHOULD** create a new Node and increase length_.
 *
 * @param p = The new node should be pointed to by p->next.
 *            If p is NULL, the new node becomes the head of the chain.
 * @param ndata = The data to be inserted.
 */
Chain::Node * Chain::insertAfter(Node * p, const Block &ndata) {
  Node* newNode = new Node(ndata);
  if (head_ == NULL) {
    head_ = newNode;
    length_++;
    return head_;
  } else if (p == NULL) {
    head_->prev = newNode;
    newNode->next = head_;
    head_ = newNode;
    length_++;
    return newNode;
  } else if (p->next == NULL) {
    newNode->prev = p;
    p->next = newNode;
    length_++;
    return newNode;
  } else {
    p->next->prev = newNode;
    newNode->prev = p;
    newNode->next = p->next;
    p->next = newNode;
    length_++;
    return newNode;
  }
}


void Chain::swap(Node *p, Node *q) {
  if (p == NULL || q == NULL || p == q) {
    return;
  }
  Node* pOldPrev = p->prev;
  Node* pOldNext = p->next;
  Node* qOldPrev = q->prev;
  Node* qOldNext = q->next;
  if (p->prev == q || q->next == p) {
    q->prev = p;
    q->next = pOldNext;
    p->prev = qOldPrev;
    p->next = q;
    if (qOldPrev != NULL) {
      qOldPrev->next = p;
    } else {
      head_ = p;
    }
    if (pOldNext != NULL) {
      pOldNext->prev = q;
    }
  } else if (q->prev == p || p->next == q) {
    p->prev = q;
    p->next = qOldNext;
    q->prev = pOldPrev;
    q->next = p;
    if (pOldPrev != NULL) {
      pOldPrev->next = q;
    } else {
      head_ = q;
    }
    if (qOldNext != NULL) {
      qOldNext->prev = p;
    }
  } else {
    p->prev = qOldPrev;
    p->next = qOldNext;
    q->prev = pOldPrev;
    q->next = pOldNext;
    if (pOldPrev != NULL) {
      pOldPrev->next = q;
    } else {
      head_ = q;
    }
    if (pOldNext != NULL) {
      pOldNext->prev = q;
    }
    if (qOldPrev != NULL) {
      qOldPrev->next = p;
    } else {
      head_ = p;
    }
    if (qOldNext != NULL) {
      qOldNext->prev = p;
    }
  }
}


/**
 * Destroys all dynamically allocated memory associated with the
 * current Chain class.
 */
void Chain::clear() {
  /* your code here */
  if (head_ == NULL) {return;}
  while (head_->next != NULL) {
    head_ = head_->next;
    delete (head_->prev);
  }
  delete head_;
  head_ = NULL;
  length_ = 0;
}

/**
 * Makes the current object into a copy of the parameter:
 * All member variables should have the same value as
 * those of other, but the memory should be completely
 * independent. This function is used in both the copy
 * constructor and the assignment operator for Chains.
 */
void Chain::copy(Chain const &other) {
  Node * currentO = head_;
  Node * otherO = other.head_;

  while (otherO) {
    currentO = insertAfter(currentO, otherO->data);
    otherO = otherO->next;
  }

}





/* Modifies the current chain:
 * 1) Find the node with the first (leftmost) block in the unscrambled
 *    image and move it to the head of the chain.
 *	This block is the one whose closest match (to the left) is the
 *	largest.  That is, the distance (using distanceTo) to this block
 *	is big for all other blocks.
 *	For each block B, find the distanceTo B from every other block
 *	and take the minimum of these distances as B's "value".
 *	Choose the block B with the maximum value over all blocks and
 *	swap its node to the head of the chain.
 *
 * 2) Starting with the (just found) first block B, find the node with
 *    the block that is the closest match to follow B (to the right)
 *    among the remaining blocks, move (swap) it to follow B's node,
 *    then repeat to unscramble the chain/image.
 */
void Chain::unscramble() {
  /* your code here */
  Node *b = head_;
  Node *first = NULL;
  Node *lastLoopMax = head_;
  while (b) {
    Node *temp = head_;
    double currentDist = temp->data.distanceTo(b->data);

    while (temp && temp != b) {
      if (temp->data.distanceTo(b->data) < currentDist) {
        first = temp;
        currentDist = temp->data.distanceTo(b->data);
      }
      temp = temp->next;
    }
    if (lastLoopMax->data.distanceTo(b->data) < first->data.distanceTo(b->data)) {
      lastLoopMax = b;
    }
    
    b = b->next;
  }
  swap(head_, first);


  b = head_;
  Node *secondEtc = NULL;
  while (b) {
    Node *temp = head_;
    double currentDist = temp->data.distanceTo(b->data);

    while (temp && temp != b) {
      if (temp->data.distanceTo(b->data) < currentDist) {
        secondEtc = temp;
      }
      temp = temp->next;
    }
    swap(b, secondEtc);

    b = b->next;
  }
  
  
}




