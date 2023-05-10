#include "Node.h"
#include "NodeManager.h"
#include "Action.h"

int main() {

	NodeManager* nm1 = new NodeManager;
	nm1->addRelation(100, 50);
	nm1->addRelation(100, 75);
	nm1->setDataToNode(15, 'A');
	nm1->addRelation(50, 10);
	nm1->addRelation(50, 9);
	nm1->addRelation(50, 8);
	nm1->addRelation(75, 15);
	nm1->setDataToNode(75, 'C');
	nm1->addRelation(75, 5);

	NodeManager* nm2 = new NodeManager;
	nm2->addRelation(50, 8);
	nm2->addRelation(100, 75);
	nm2->addRelation(75, 5);
	nm2->setDataToNode(5, 'B');
	nm2->addRelation(50, 10);
	nm2->addRelation(100, 50);
	nm2->addRelation(75, 15);
	nm2->setDataToNode(15, 'A');
	nm2->addRelation(50, 9);

	const Node& root1 = nm1->getNode(100);
	const Node& root2 = nm2->getNode(100);

	//cout << root1 << endl;
	//cout << root2 << endl;
	
	Action* action = new CompleteAction(root1);
	Node* completeTree = action->act(&root2);

	cout << *completeTree << endl;
	
	delete action;
	delete completeTree;
	delete nm1;
	delete nm2;

	return 0;
}