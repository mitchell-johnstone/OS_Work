/* stackm.h
 * 
 * External (public) declarations for stack machine in C.
 * 
 * This stack will know about the top.  Each element must point 
 * to the one below it in the stack.  
 * 
 * Note that the pop operations do not return a reference to the
 * popped node.  This would require storage for the node to be
 * released by the user, which could lead to memory mishandling.
 * The stack size is unbounded so memory must be allocated and
 * freed as appropriate when operations are performed.
 * 
 * This stack will only hold integers.  Mathematical operations are
 * performed on elements on the top of the stack as described in the
 * function definitions.
 * 
 */

#ifndef STACKM_H
#define STACKM_H

/* Structures */

/* a stack node */
typedef struct node {
    int value;
    struct node* next;
} node;

/* The stack itself */
typedef struct stackm {
    struct node *top;
} stackm;

/* Stack Machine methods
 * 
 * These methods are used to create and operate on the stack machine as a whole.
 */

/* smInit()
 *     Initialize a stack machine structure.  An empty stack will
 *     be characterized by top being NULL.
 *         Parameters:  myStack - a pointer to the structure to be init
 *         Returns: void
 */
void smInit(struct stackm *myStack);

/* smSize()
 *     Reports the current size of the stack.  Will need to iterate
 *     the stack to get this data size there is no size property, nor
 *     can there really be one given that users can access nodes.
 *         Parameters:  myStack - the stack
 *         Returns: int, size of stack
 */
int smSize(struct stackm *myStack);

/* smPush()
 *     Add a new node with provided data to the top of the stack.
 *     This method should allocate memory as needed and check to
 *     make sure that the memory was allocated successfully.
 *         Parameters:  myStack - the stack
 *                      toStore - the value to store
 *         Returns: int - 0 if no push could be performed 
 *                        (failed to allocate memory) or non-zero
 *                        if push was successful
 */
int smPush(struct stackm *myStack, int toStore);

/* smPop()
 *     Removes top item in stack.  Note, this does not return
 *     any data from the stack.  If the data in the node is needed
 *     it should be accessed prior to the pop (smTop).
 *         Parameters:  myStack - the stack
 *         Returns: int - 0 if no pop (stack was empty) or non-zero
 *                        if pop successful
 */
int smPop(struct stackm *myStack);

/* smTop()
 *     return the value at the top of the stack.  NOTE: the value
 *     must be returned by dereferencing the passed in pointer.
 *     The function must make sure the pointer is not NULL prior to
 *     dereferencing to avoid memory violations.
 *         Parameters:  myStack - the stack
 *                      toStore - a point to store the stack top value
 *         Returns: int - 0 if top could not be retrieved
 *                        (toStore was NULL or stack is empty) or 
 *                        non-zero retrieval was successful
 */
int smTop(struct stackm *myStack, int* toStore);

/* smClear()
 *     Clears all nodes and releases all dynamic memory.  Stack
 *     structure should be NULLed and can be reused.  
 *         Parameters:  myStack - the stack
 *         Returns: nothing
 */
void smClear(struct stackm *myStack);

/* smPrint()
 *     Prints the contents of the stack machine to standard output.
 *     When printing it should be clear what value contains the top
 *     as well which which values are stacked on top of other values  
 *         Parameters:  myStack - the stack
 *         Returns: nothing
 */
void smPrint(struct stackm *myStack);

/* Stack Machine manipulation methods
 * 
 * These methods perform operations that manipulate the stack
 * (math or element ordering).
 */

/* smAdd()
 *     Add together the top two elements of the stack and push
 *     the result.
 *     The stack must contain at least 2 elements for this
 *     operation to be successful.
 *     Any removed element must be freed (no memory leaks)
 *         Parameters:  myStack - the stack
 *         Returns: int - 0 if operation could not be performed
 *                        (not enough elements on the stack) 
 *                        non-zero if successful
 */
int smAdd(struct stackm* myStack);

/* smSub()
 *     Subtract the top two elements of the stack and push
 *     the result.
 *     The stack must contain at least 2 elements for this
 *     operation to be successful.
 *     Operation is TOS (top of stack) - 2nd from TOS
 *     if the stack contained the values:
 *     top ->    6
 *               5
 *               4
 *     bottom -> 3
 *     The result after a smSub operation would be:
 *     top ->    1
 *               4
 *     bottom -> 3
 *     6 - 5 = 1
 *     Any removed element must be freed (no memory leaks)
 *         Parameters:  myStack - the stack
 *         Returns: int - 0 if operation could not be performed
 *                        (not enough elements on the stack) 
 *                        non-zero if successful
 */
int smSub(struct stackm* myStack);

/* smMult()
 *     Multiply the top two elements of the stack and push
 *     the result.
 *     The stack must contain at least 2 elements for this
 *     operation to be successful.
 *     Any removed element must be freed (no memory leaks)
 *         Parameters:  myStack - the stack
 *         Returns: int - 0 if operation could not be performed
 *                        (not enough elements on the stack) 
 *                        non-zero if successful
 */
int smMult(struct stackm* myStack);

/* smRotate()
 *     Rotate the top 'n' elements of the stack.  For example,
 *     if the stack contained the values:
 *     top ->    6
 *               5
 *               4
 *     bottom -> 3
 *     The result after a rotate 3 operation would be:
 *     top ->    5
 *               4
 *               6
 *     bottom -> 3
 *     NOTE: the top element on the stack goes to the 'nth'
 *     location and every element above the 'nth' location
 *     gets moved up one
 *     The stack must contain at least 'n' elements for this
 *     operation to be successful.
 *     'n' must be greater than or equal to 1.  A value of 1
 *     does nothing, but is still successfull.
 *     Any removed element must be freed (no memory leaks)
 *         Parameters:  myStack - the stack
 *                      depth - the depth of the rotation
 *         Returns: int - 0 if operation could not be performed
 *                        (not enough elements on the stack
 *                        or depth is too small) 
 *                        non-zero if successful
 */
int smRotate(struct stackm* myStack, int depth);

#endif
