#include "LinkedList.h"
#include "Stack.h"
#include "Queue.h"
#include "ValidParentheses.h"
#include <cassert>

// run .\tests.exe to execute file

int main(){


    //Linked List Tests

    // We check if given empty linked list does it return true.
    double_linked_list<int> empty = {};
    assert(empty.isEmpty());

    double_linked_list<int> push = {};
    // WE test adding a 7 node to empty list and see if header and tail are set correctly.
    push.pushFront(7);
    assert(!push.isEmpty());
    assert(push.head == push.tail);
    assert(push.head->value == 7);
    assert(push.head->next_node == nullptr);
    assert(push.head->prev_node == nullptr);

    // We then add anotehr node with 20 and see if the tail, head, previous and forward node values are correct for each node.
    push.pushFront(20);
    assert(push.head->value == 20);
    assert(push.head->prev_node == nullptr);
    assert(push.head->next_node == push.tail);
    assert(push.tail->value == 7);
    assert(push.tail->prev_node == push.head);
    assert(push.tail->next_node == nullptr);

    double_linked_list<int> back_list{};
    //First pushback test where we see if tail is set correctly if given empty linked list
    back_list.pushBack(7);
    assert(back_list.head == back_list.tail);
    assert(back_list.head->value == 7);
    //second test now taht we have node with value 7 see if the new node send it to become the tail given that the linked list is not empty.
    back_list.pushBack(20);
    assert(back_list.head->value == 7);
    assert(back_list.tail->value == 20);
    assert(back_list.head->next_node == back_list.tail);
    assert(back_list.tail->prev_node == back_list.head);

    double_linked_list<int> peek_list{};
    //Tests what happens with empty list should return nothing
    assert(!peek_list.peekFront().has_value());
    //Tests if we put value in the front it should now return a value
    peek_list.pushFront(0);
    assert(peek_list.peekFront().has_value());
    assert(peek_list.peekFront().value() == 0);
    //Tests if we put something it the back the front value should remain the same
    peek_list.pushBack(7);
    assert(peek_list.peekFront().value() == 0); // Peeking didn't remove it

    double_linked_list<int> back_peek{};
    assert(!back_peek.peekBack().has_value()); // Test with empty list
    back_peek.pushFront(0);
    assert(back_peek.peekBack().value() == 0); // One node
    back_peek.pushBack(7);
    assert(back_peek.peekBack().value() == 7); // New tail
    back_peek.pushFront(9);
    assert(back_peek.peekBack().value() == 7); // Changing the front node didn't change the back
    
    double_linked_list<int> list{};
    //Test when list is empty
    assert(!list.popFront().has_value());
    //Test if when list has one element after popping list should be empty.
    list.pushFront(7);
    assert(list.popFront().value() == 7);
    assert(list.isEmpty());
    //Test when mulitple elements in list does it update the as elements get removed.
    list.pushBack(10);
    list.pushBack(20);
    assert(list.popFront().value() == 10);
    assert(list.peekFront().value() == 20);
    assert(list.head->prev_node == nullptr);

    double_linked_list<int> pop_back_list{};
    //test popback when list is empty.
    assert(!pop_back_list.popBack().has_value());
    //test popback when list only has one node.
    pop_back_list.pushFront(7);
    assert(pop_back_list.popBack().value() == 7);
    assert(pop_back_list.isEmpty());
    //tes popback when list has many node and updates correctly on each one.
    pop_back_list.pushBack(10);
    pop_back_list.pushBack(20);
    assert(pop_back_list.popBack().value() == 20);
    assert(pop_back_list.peekBack().value() == 10);
    assert(pop_back_list.tail->next_node == nullptr);

    //Stack Tests

    Stack<int> stack{};
    //check if stack is empty
    assert(stack.isEmpty());
    assert(!stack.peek().has_value());
    assert(!stack.pop().has_value());

    stack.push(7);
    stack.push(20);
    assert(!stack.isEmpty());
    // Peek does not remove it
    assert(stack.peek().value() == 20);
    assert(stack.peek().value() == 20);
    // Last in, first out
    assert(stack.pop().value() == 20);
    assert(stack.pop().value() == 7);
    assert(stack.isEmpty());
    assert(!stack.pop().has_value());

    //Queue Tests

    Queue<int> queue{};
    //Check when empty Queue
    assert(queue.isEmpty());
    assert(!queue.peek().has_value());
    assert(!queue.dequeue().has_value());

    queue.enqueue(7);
    queue.enqueue(20);
    assert(!queue.isEmpty());
    assert(queue.peek().value() == 7);
    // Peek does not remove it
    assert(queue.peek().value() == 7);
    // First in, first out
    assert(queue.dequeue().value() == 7);
    assert(queue.peek().value() == 20);
    //Check values are we get rid of elements from the queue
    queue.enqueue(30);
    assert(queue.dequeue().value() == 20);
    assert(queue.dequeue().value() == 30);
    assert(queue.isEmpty());
    assert(!queue.dequeue().has_value());

    //Valid Parenthesis Tests
    //Main situations I could think of
    assert(isValidParentheses("()"));
    assert(isValidParentheses("()[]{}"));   // separate pairs
    assert(isValidParentheses("([{}])"));  // nested pairs
    assert(!isValidParentheses("(]"));     // wrong bracket type
    assert(!isValidParentheses("([)]"));   // wrong nesting order
    assert(!isValidParentheses(")"));      // closing with nothing open
    assert(!isValidParentheses("()("));    // opening left over
    assert(!isValidParentheses("())"));    // extra closing

    return 0;
}