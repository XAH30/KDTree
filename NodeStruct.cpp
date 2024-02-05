struct Node {
    Point point;
    Node* left;
    Node* right;

    Node(const Point& p) : point(p), left(nullptr), right(nullptr) {}
};