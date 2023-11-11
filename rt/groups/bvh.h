#ifndef CG1RAYTRACER_GROUPS_BVH_HEADER
#define CG1RAYTRACER_GROUPS_BVH_HEADER

#include <rt/groups/group.h>
#include <rt/bbox.h>

namespace rt {

    // class for creating a node containing info about leaf and internal node;
    class BVHBuildNode {
    public:
        // BVHBuildNode Public Methods
        void InitLeaf(const BBox& b, const std::vector<Primitive*> p)
        {
            isleaf = true;
            nPrimitives = p.size();
            bounds = b; // complete bounds of primitive in leaf node
            children[0] = children[1] = nullptr;
            pri = p;
        }
        void InitInterior(int axis, BVHBuildNode* c0, BVHBuildNode* c1)
        {
            //isleaf = false;
            children[0] = c0;
            children[1] = c1;
            c0->bounds.extend(c1->bounds);
            bounds = c0->bounds; // box bound of the node
            splitAxis = axis;
            nPrimitives = 0;
        }

        // Tree construction parameters;
        bool isleaf;
        BBox bounds = bounds.empty();
        BVHBuildNode* children[2];
        size_t splitAxis, nPrimitives, firstPrimOffset;
        std::vector<Primitive*> pri; // contains primitives in leaf nodes
    };

    struct BVHPrimitiveInfo {
        BVHPrimitiveInfo() {}
        BVHPrimitiveInfo(size_t primitiveNumber, const BBox& bounds)
            : primitiveNumber(primitiveNumber),
            bounds(bounds),
            centroid(.5f * bounds.min + .5f * bounds.max) {}
        size_t primitiveNumber;
        BBox bounds;
        Point centroid;
    };

    struct LinearBVHNode {
        BBox bounds;
        union {
            int primitivesOffset;   // leaf
            int secondChildOffset;  // interior
        };
        uint16_t nPrimitives;  // 0 -> interior node
        uint8_t axis;          // interior node: xyz
        uint8_t pad[1];        // ensure 32 byte total size

    };
    class BVH : public Group {

    public:
        BVH();

        // class for split method
        enum class SplitMethod { SAH, Middle, EqualCounts};
        const static SplitMethod splitMethod = SplitMethod::Middle;

        std::vector<Primitive*> unboundPri;

        BVHBuildNode* root = nullptr;
        LinearBVHNode* nodes = nullptr;
        int flattenBVHTree(BVHBuildNode* node, int* offset);

        virtual BBox getBounds() const;
        virtual Intersection intersect(const Ray& ray, float previousBestDistance = FLT_MAX) const;
        virtual void rebuildIndex();
        virtual void add(Primitive* p);
        virtual void setMaterial(Material* m);
        virtual void setCoordMapper(CoordMapper* cm);

        // Do not use this structure as your node layout:
        // It is inefficient and has a large memory footprint.
        struct SerializedNode {
            bool isLeaf;
            BBox bbox;

            // For leaves only
            std::vector<Primitive*> primitives;

            // For internal nodes only
            size_t leftChildId;
            size_t rightChildId;
        };

        // Implement this function if you want to take part in the BVH speed competition
        struct Output {
            virtual void setNodeCount(size_t nodeCount) = 0;
            virtual void setRootId(size_t rootId) = 0;
            virtual void writeNode(size_t nodeId, const SerializedNode& node) = 0;
        };
        void serialize(Output& output);

        // Implementing this is optional and not needed for the BVH speed competition,
        // but it will allow you to run the benchmark utility and test your BVH exporter.
        struct Input {
            virtual size_t getNodeCount() = 0;
            virtual size_t getRootId() = 0;
            virtual const SerializedNode& readNode(size_t nodeId) = 0;
        };
        void deserialize(Input& input);
    };

}

#endif