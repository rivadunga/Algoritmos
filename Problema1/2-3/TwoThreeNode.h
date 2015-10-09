
// TwoThreeNode class
template<class T>
class TwoThreeNode {
    private:

        void insert1Siblings(TwoThreeNode<T> *newChild, int newSmallest) {
            int newKey = newChild->key[0];
            newChild->parent = this;

            if (newKey < child[0]->key[0]) {
                child[1] = child[0];
                child[0] = newChild;
                key[0] = child[1]->getSmallest();
            }
            else {
                child[1] = newChild;
                key[0] = newSmallest;
            }
        }

        void insert2Siblings(TwoThreeNode<T> *newChild, int newSmallest) {
            int newKey = newChild->key[0];
            newChild->parent = this;

            if (newKey < child[0]->key[0]) {
                child[2] = child[1];
                child[1] = child[0];
                child[0] = newChild;

                key[1] = key[0];
                key[0] = child[1]->getSmallest();
                updateParentSmallest(newSmallest);
            }
            else if (newKey < child[1]->key[0]) {
                child[2] = child[1];
                child[1] = newChild;

                key[1] = key[0];
                key[0] = newSmallest;
            }
            else {
                child[2] = newChild;

                key[1] = newSmallest;
            }
        }

        void insert3Siblings(TwoThreeNode<T> *newChild, int newSmallest) {
            int newKey = newChild->key[0];

            int splitSmallest = -1;
            TwoThreeNode<T> *splitNode = new TwoThreeNode<T>();
            splitNode->parent = parent;

            if (newKey < child[0]->key[0] || newKey < child[1]->key[0]) {
                splitSmallest = key[0];
                splitNode->child[0] = child[1];
                splitNode->child[1] = child[2];
                splitNode->key[0] = key[1];

                child[1]->parent = splitNode;
                child[2]->parent = splitNode;
                newChild->parent = this;

                if (newKey < child[0]->key[0]) {
                    child[1] = child[0];
                    child[0] = newChild;

                    key[0] = child[1]->getSmallest();
                    updateParentSmallest(newSmallest);
                }
                else {
                    child[1] = newChild;

                    key[0] = newSmallest;
                }
            }
            else {
                child[2]->parent = splitNode;
                newChild->parent = splitNode;

                if (newKey < child[2]->key[0]) {
                    splitSmallest = newSmallest;
                    splitNode->child[0] = newChild;
                    splitNode->child[1] = child[2];
                    splitNode->key[0] = key[1];
                }
                else {
                    splitSmallest = key[1];
                    splitNode->child[0] = child[2];
                    splitNode->child[1] = newChild;
                    splitNode->key[0] = newSmallest;
                }
            }

            child[2] = nullptr;
            key[1] = -1;

            if (parent->parent == nullptr) {
                TwoThreeNode<T> *newNode = new TwoThreeNode<T>();

                parent->child[0] = newNode;
                newNode->parent = parent;
                newNode->child[0] = this;
                parent = newNode;
            }

            parent->insert(splitNode, splitSmallest);
        }


        void updateParentSmallest(int data) {
            switch (sibNumber()) {
                case 0: if (parent->parent != nullptr) parent->updateParentSmallest(data); break;
                case 1: parent->key[0] = data; break;
                case 2: parent->key[1] = data; break;
            }
        }

    public:
        int key[2];
        TwoThreeNode<T> *parent, *child[3];

        TwoThreeNode<T>(int data = -1) {
            key[0] = data;
            key[1] = -1;
            parent = child[0] = child[1] = child[2] = nullptr;
        }

        bool isLeaf() {
            return (child[0] == nullptr);
        }

        int sibNumber() {
            for (int i = 0; i < 3; ++i) {
                if (this == parent->child[i]) return i;
            }
            return -1;
        }

        TwoThreeNode<T>*& getChildAt(int index){
            return child[index];
        }

        int getSize(){
            int size = 0;
            for (int i = 0; i < 3; ++i){
                if (child[i] != nullptr)
                    size++;
            }
        }

        int getSmallest() {
            TwoThreeNode<T> *node = this;
            while (!node->isLeaf()) node = node->child[0];
            return node->key[0];
        }

        void insert(TwoThreeNode<T> *newChild, int newSmallest) {
            if (child[1] == nullptr) insert1Siblings(newChild, newSmallest);
            else if (child[2] == nullptr) insert2Siblings(newChild, newSmallest);
            else insert3Siblings(newChild, newSmallest);
        }
};
