class KDTree {
public:
    KDTree() : k(0), root(nullptr) {}

    void insert(const Point& point);

    bool remove(const Point& point);

    void divideNode(const Point& point);

    Point findNearestNeighbor(const Point& queryPoint);

private:
    Node* root;
    size_t k;
    Point nearestNeighbor;
    double bestDistance;

    Node* build(std::vector<Point>& points, int start, int end, int depth);

    void sortByAxis(std::vector<Point>& points, int start, int end, int axis);

    void insertRecursive(Node* node, const Point& point, int depth);

    bool removeRecursive(Node*& node, const Point& point, int depth);

    Node* findSuccessor(Node* node);

    void divideNodeRecursive(Node* node, const Point& point, int depth);

    double distance(const Point& p1, const Point& p2);

    void search(Node* node, const Point& queryPoint, int depth);
};