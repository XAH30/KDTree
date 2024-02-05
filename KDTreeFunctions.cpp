void KDTree::insert(const Point& point) {
    if (root == nullptr) {
        k = point.coordinates.size();
        root = new Node(point);
    }
    else {
        insertRecursive(root, point, 0);
    }
}

bool KDTree::remove(const Point& point) {
    return removeRecursive(root, point, 0);
}

void KDTree::divideNode(const Point& point) {
    divideNodeRecursive(root, point, 0);
}

Point KDTree::findNearestNeighbor(const Point& queryPoint) {
    nearestNeighbor = root->point;
    bestDistance = std::numeric_limits<double>::infinity();
    search(root, queryPoint, 0);
    return nearestNeighbor;
}

Node* KDTree::build(std::vector<Point>& points, int start, int end, int depth) {
    if (start > end) {
        return nullptr;
    }

    int axis = depth % k;
    int median = (start + end) / 2;

    sortByAxis(points, start, end, axis);

    Node* node = new Node(points[median]);
    node->left = build(points, start, median - 1, depth + 1);
    node->right = build(points, median + 1, end, depth + 1);

    return node;
}

void KDTree::sortByAxis(std::vector<Point>& points, int start, int end, int axis) {
    std::sort(points.begin() + start, points.begin() + end, [axis](const Point& p1, const Point& p2) {
        return p1.coordinates[axis] < p2.coordinates[axis];
        });
}

void KDTree::insertRecursive(Node* node, const Point& point, int depth) {
    int axis = depth % k;

    if (point.coordinates[axis] < node->point.coordinates[axis]) {
        if (node->left == nullptr) {
            node->left = new Node(point);
        }
        else {
            insertRecursive(node->left, point, depth + 1);
        }
    }
    else {
        if (node->right == nullptr) {
            node->right = new Node(point);
        }
        else {
            insertRecursive(node->right, point, depth + 1);
        }
    }
}

bool KDTree::removeRecursive(Node*& node, const Point& point, int depth) {
    if (node == nullptr) {
        return false;
    }

    int axis = depth % k;

    if (point.coordinates[axis] < node->point.coordinates[axis]) {
        return removeRecursive(node->left, point, depth + 1);
    }
    else if (point.coordinates[axis] > node->point.coordinates[axis]) {
        return removeRecursive(node->right, point, depth + 1);
    }
    else {
        if (node->point.coordinates == point.coordinates) {
            if (node->left == nullptr && node->right == nullptr) {
                delete node;
                node = nullptr;
            }
            else if (node->left != nullptr && node->right == nullptr) {
                Node* temp = node;
                node = node->left;
                delete temp;
            }
            else if (node->left == nullptr && node->right != nullptr) {
                Node* temp = node;
                node = node->right;
                delete temp;
            }
            else {
                Node* successor = findSuccessor(node->right);
                node->point = successor->point;
                removeRecursive(node->right, successor->point, depth + 1);
            }
            return true;
        }
        else {
            return removeRecursive(node->right, point, depth + 1);
        }
    }
}

Node* KDTree::findSuccessor(Node* node) {
    Node* current = node->right;
    while (current != nullptr && current->left != nullptr) {
        current = current->left;
    }
    return current;
}

void KDTree::divideNodeRecursive(Node* node, const Point& point, int depth) {
    if (node == nullptr) {
        return;
    }

    int axis = depth % k;

    if (point.coordinates[axis] < node->point.coordinates[axis]) {
        divideNodeRecursive(node->left, point, depth + 1);
    }
    else {
        divideNodeRecursive(node->right, point, depth + 1);
    }

    if (depth % k == 0 && point.coordinates[axis] == node->point.coordinates[axis]) {
        divideNodeRecursive(node->left, point, depth + 1);
        divideNodeRecursive(node->right, point, depth + 1);
    }
}

double KDTree::distance(const Point& p1, const Point& p2) {
    double dist = 0.0;
    for (size_t i = 0; i < k; i++) {
        dist += pow(p1.coordinates[i] - p2.coordinates[i], 2);
    }
    return sqrt(dist);
}

void KDTree::search(Node* node, const Point& queryPoint, int depth) {
    if (node == nullptr) {
        return;
    }

    double dist = distance(node->point, queryPoint);
    if (dist < bestDistance) {
        nearestNeighbor = node->point;
        bestDistance = dist;
    }

    int axis = depth % k;
    if (queryPoint.coordinates[axis] < node->point.coordinates[axis]) {
        search(node->left, queryPoint, depth + 1);
        if (bestDistance > abs(queryPoint.coordinates[axis] - node->point.coordinates[axis])) {
            search(node->right, queryPoint, depth + 1);
        }
    }
    else {
        search(node->right, queryPoint, depth + 1);
        if (bestDistance > abs(queryPoint.coordinates[axis] - node->point.coordinates[axis])) {
            search(node->left, queryPoint, depth + 1);
        }
    }
}
