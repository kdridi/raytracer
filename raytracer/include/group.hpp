#ifndef __GROUP_HPP__
#define __GROUP_HPP__

#include "intersections.hpp"
#include "shape.hpp"

namespace raytracer {

    class Group : public AShape {
    public:
        static Shape *Hexagon();

    public:
        Group();
        virtual ~Group();

    public:
        Intersections localIntersect(const Ray &) const override;
        Vector localNormalAt(const Point &) const override;
        Bounds bounds() const override;

    public:
        void add(Shape *);
        void remove(Shape *);
        bool empty() const;
        std::size_t size() const;
        Shape &operator[](std::size_t) const;

    private:
        std::vector<Shape *> m_shapes;
    };

#include <algorithm>
#include <limits>
#include <vector>

    class KDTree : public AShape {
    public:
        KDTree(std::vector<Shape *> shapes, int maxDepth = 10) : AShape(), m_maxDepth(maxDepth)
        {
            for (auto &shape : shapes)
                m_shapes.push_back(shape);
            m_root = build(0, m_shapes.begin(), m_shapes.end(), 0);
        }

        ~KDTree()
        {
            for (auto &shape : m_shapes)
                delete shape;
            delete m_root;
        }

        Intersections localIntersect(const Ray &ray) const override
        {
            Intersections result;
            if (m_root) {
                intersectNode(ray, m_root, result);
            }
            return result;
        }

        Vector localNormalAt(const Point &point) const override
        {
            throw std::runtime_error("KDTree::localNormalAt should never be called.");
        }

        Bounds bounds() const override
        {
            return m_root ? m_root->bounds : Bounds(Point(0, 0, 0), Point(0, 0, 0));
        }

    private:
        struct Node {
            Node() : bounds(Point(0, 0, 0)), left(nullptr), right(nullptr), shapes() {}
            Bounds bounds;
            Node *left;
            Node *right;
            std::vector<Shape *> shapes;
        };

        Node *build(int depth, std::vector<Shape *>::iterator begin, std::vector<Shape *>::iterator end, int axis)
        {
            if (begin == end) {
                return nullptr;
            }

            if (depth >= m_maxDepth || std::distance(begin, end) <= 1) {
                Node *node = new Node();
                node->left = node->right = nullptr;
                node->shapes.assign(begin, end);
                for (auto shape : node->shapes) {
                    node->bounds += shape->bounds();
                }
                return node;
            }

            auto middle = begin + (end - begin) / 2;
            std::nth_element(begin, middle, end, [axis](const Shape *a, const Shape *b) {
                return a->bounds().center()[axis] < b->bounds().center()[axis];
            });

            Node *node = new Node();
            node->left = build(depth + 1, begin, middle, (axis + 1) % 3);
            node->right = build(depth + 1, middle, end, (axis + 1) % 3);

            if (node->left)
                node->bounds += node->left->bounds;

            if (node->right)
                node->bounds += node->right->bounds;

            return node;
        }

        void intersectNode(const Ray &ray, const Node *node, Intersections &result) const
        {
            if (!node->bounds.intersect(ray))
                return;

            for (const auto &shape : node->shapes)
                result.add(shape->intersect(ray));

            if (node->left)
                intersectNode(ray, node->left, result);

            if (node->right)
                intersectNode(ray, node->right, result);
        }

        int m_maxDepth;
        Node *m_root;
        std::vector<Shape *> m_shapes;
    };

} // namespace raytracer

#endif // __GROUP_HPP__
