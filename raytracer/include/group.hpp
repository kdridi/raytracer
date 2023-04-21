#ifndef __GROUP_HPP__
#define __GROUP_HPP__

#include "shape.hpp"

namespace raytracer {

    class Group : public AShape {
    public:
        static Shape *Hexagon();
        static Group *CreateOctreeGroup(std::vector<Shape *> &shapes, int depth = 3);

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

} // namespace raytracer

#endif // __GROUP_HPP__
