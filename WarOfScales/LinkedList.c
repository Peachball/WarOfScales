#include "LinkedList.h"

void NodeList_Init(NodeList* list)
{
	list->headNode = NULL;
	list->lastNode = NULL;
	list->listSize = 0;
}
NodeList* NodeList_Create()
{
	Node* n = malloc(sizeof(NodeList));
	NodeList_Init(n);
	return n;
}
void NodeList_AddNode(NodeList* list, Node* n)
{
	if (list->lastNode != NULL)
	{
		list->lastNode->nextNode = n;
	}
	n->previousNode = list->lastNode;
	if (list->listSize == 0)
	{
		list->headNode = n;
		list->lastNode = n;
	}
	list->lastNode = n;
	n->index = list->listSize;
	list->listSize++;
}
void NodeList_PushNode(NodeList* list, Node* n)
{
	Node* temp = list->headNode;
	n->nextNode = list->headNode;
	list->headNode->previousNode = n;
	list->headNode = n;
	n->index = 0;
	while (temp != NULL)
	{
		temp->index++;
		temp = temp->nextNode;
	}
	list->listSize++;
}
void NodeList_InsertNode(NodeList* list, Node* leftnode, Node* node)
{
	
	if (leftnode == NULL)
	{
		NodeList_AddNode(list, node);
	}
	else
	{
		Node* temp = leftnode->nextNode;
		leftnode->nextNode = node;
		node->previousNode = leftnode;
		if (temp != NULL)  //temp is the original leftnode->nextNode
		{
			temp->previousNode = node;
			node->nextNode = temp;
			while (temp != NULL)
			{
				temp->index++;
				temp = temp->nextNode;
			}
		}
		else
		{
			list->lastNode = node;
		}
		list->listSize++;
	}
}
BOOLEAN NodeList_Contains(NodeList* list, Node* n)
{
	Node* temp = list->headNode;
	if (n == NULL)
	{
		printf("Error in function NodeList_Contains: n is null!\n");
		return FALSE;
	}
	while (temp != NULL)
	{
		if (temp == n)
		{
			return TRUE;
		}
		temp = temp->nextNode;
	}
	return FALSE;
}
void NodeList_RemoveNode(NodeList* list, Node* n, BOOLEAN destroy)
{
	if (NodeList_Contains(list, n))
	{
		if (n->nextNode == NULL && n->previousNode != NULL) //if is last node
		{
			n->previousNode->nextNode = NULL;
			n->previousNode = NULL;
		}
		else if (n->nextNode != NULL && n->previousNode == NULL) //if is first node
		{
			Node* temp = n->nextNode;
			list->headNode = n->nextNode;
			n->nextNode->previousNode = NULL;
			n->nextNode = NULL;
			while (temp != NULL)
			{
				temp->index--;
				temp = temp->nextNode;
			}
		}
		else if (n->nextNode != NULL && n->previousNode != NULL)
		{
			Node* temp = n->nextNode;
			n->nextNode->previousNode = n->previousNode;
			n->previousNode->nextNode = n->nextNode;
			n->nextNode = NULL;
			n->previousNode = NULL;
			while (temp != NULL)
			{
				temp->index--;
				temp = temp->nextNode;
			}
		}
		list->listSize -= list->listSize > 0 ? 1 : 0;
		if (destroy)
		{
			Node_Destroy(n);
		}
		else
		{
			free(n);
		}
	}
	else
	{
		printf("Error in function NodeList_RemoveNode: Tried to remove a node from a list it does not exist in\n");
	}
}
void NodeList_FindUIElement(Node** output, NodeList* list, struct UIElement* element)
{
	Node* temp = list->headNode;
	while (temp != NULL)
	{
		if (temp->UIElement == element)
		{
			*output = temp;
			return;
		}
	}
	*output = NULL;
	printf("Could not find element in function NodeList_FindUIElement!\n");
}
void NodeList_Clear(NodeList* list)
{
	Node* temp = list->headNode;
	while (temp != NULL)
	{
		Node* tempnext = temp->nextNode;
		temp->nextNode = NULL;
		temp->previousNode = NULL;
		temp = tempnext;
	}
	list->headNode = NULL;
	list->lastNode = NULL;
	list->listSize = 0;
}
Node* NodeList_GetNode(NodeList* list, int depth, BOOLEAN reverse)
{
	int d = reverse ? list->listSize - depth - 1 : depth;
	if (list == NULL || (unsigned int)list != 0xcccccccc)
	{
		printf("Error in function NodeList_GetNode: n was null!\n");
		return NULL;
	}
	if (list->listSize / 2 > depth)
	{
		return Node_GetNode(list->headNode, d, FALSE);
	}
	else
	{
		return Node_GetNode(list->lastNode, list->listSize - depth - 1, TRUE);
	}
}
void NodeList_ReverseListOrder(NodeList* list)
{
	if (list->listSize >= 2)
	{
		Node* temp = list->headNode;
		list->headNode = list->lastNode;
		list->lastNode = temp;
		while (temp != NULL)
		{
			Node* tempNext = temp->nextNode;
			temp->nextNode = temp->previousNode;
			temp->previousNode = tempNext;
			temp->index = list->listSize - temp->index - 1;
			temp = tempNext;
		}
	}
}
void NodeList_Print(NodeList* list)
{
	Node* temp = list->headNode;
	printf("List %p: (size %i)\n", list, list->listSize);
	if (temp == NULL)
	{
		printf("lol fuk\n");
	}
	while (temp != NULL)
	{
		printf("Element index %i, val %f, address %p, previous %p, next %p\n", temp->index, temp->val, temp, temp->previousNode, temp->nextNode);
		temp = temp->nextNode;
	}
}
void Node_Copy(Node* output, Node* input)
{
	memcpy(output, input, sizeof(Node));
}
void Node_Destroy(Node* node)
{
	//TODO update this shit
#define Y(k) if(node->k != NULL) { free(node->k); node->k = NULL;}
	MEMBER_MAP(Y)
#undef Y
	free(node);
}
void Node_Init(Node* node)
{
	//TODO update this shit
	node->index = 0;
	node->val = 0;
	node->x = 0;
	node->y = 0;
	node->w = 0;
	node->h = 0;
	node->nextNode = NULL;
	node->previousNode = NULL;
#define Y(k) node->k = NULL;
	MEMBER_MAP(Y)
#undef Y
	node->texture = NULL;
}
Node* Node_Create()
{
	Node* n = malloc(sizeof(Node));
	Node_Init(n);
	return n;
}
Node* Node_GetNode(Node* n, int depth, BOOLEAN reverse)
{
	int i = 0;
	Node* temp = n;
	if (n == NULL || (unsigned int)n != 0xcccccccc)
	{
		printf("Error in function Node_GetNode: n was null!\n");
		return NULL;
	}
	if (depth == 0)
	{
		return n;
	}
	if (reverse == FALSE)
	{
		for (i = depth; i > 0; i--)
		{
			if (temp->nextNode == NULL)
			{
				return NULL;
			}
			temp = temp->nextNode;
		}
		return temp; //could be problematic, what if since temp is no longer in the scope it gets wiped
	}
	else
	{
		for (i = depth; i > 0; i--)
		{
			if (temp->previousNode == NULL)
			{
				return NULL;
			}
			temp = temp->previousNode;
		}
		return temp; //could be problematic, what if since temp is no longer in the scope it gets wiped
	}
}