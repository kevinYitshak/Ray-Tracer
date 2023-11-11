#include <rt/groups/bvh.h>
//#include <glog/logging.h>
//--------------------------

namespace rt {
	BVH::BVH()
	{
	}

	struct BucketInfo
	{
		int count = 0;
		BBox bucketBounds = bucketBounds.empty();
	};

	Vector Offset(const Point& p, const BBox& box) {
		Vector o = p - box.min;
		if (box.max.x > box.min.x) o.x /= box.max.x - box.min.x;
		if (box.max.y > box.min.y) o.y /= box.max.y - box.min.y;
		if (box.max.z > box.min.z) o.z /= box.max.z - box.min.z;
		return o;
	}

	int MaximumExtent(BBox& box)
	{
		Vector d = box.diagonal();
		if (d.x > d.y && d.x > d.z)
			return 0;
		else if (d.y > d.z)
			return 1;
		else
			return 2;
	}

	float getVal(const Point p, int dim)
	{
		if (dim == 0) { return p.x; }
		else if (dim == 1) { return p.y; }
		else { return p.z; }
	}

	float getVal(const Vector p, int dim)
	{
		if (dim == 0) { return p.x; }
		else if (dim == 1) { return p.y; }
		else { return p.z; }
	}

	BVHBuildNode* recursiveBuild(std::vector<BVHPrimitiveInfo>& primitiveInfo, int start,
		int end, int* totalNodes,
		std::vector<Primitive*>& orderedPrims, std::vector<Primitive*>& primitives)
	{
		// everytime recursiveBuild is called create memory in heap;
		BVHBuildNode* node = new BVHBuildNode();
		(*totalNodes)++;

		// primitive size
		size_t nPrimitives = primitives.size();

		// compute bounds of all the primitives in the BVH node;
		BBox bounds = bounds.empty();

		// compute bound of all the primitives center to calculate split axis;
		BBox cbound = cbound.empty();

		for (size_t i = 0; i < nPrimitives; ++i)
		{
			bounds.extend(primitives[i]->getBounds());
			cbound.extend(primitives[i]->getBounds().center);
		}

		// create vector of type Primitive to store the primitives in leaf node;
		std::vector<Primitive*> leaf_pri;

		if (nPrimitives > 2) // stopping condition for the recursion;
		{
			int dim; // axis along which the node has to partition
			Vector diag = cbound.diagonal();

			float len_max = std::max(diag.x, std::max(diag.y, diag.z));
			dim = (len_max == diag.x) ? 0 : 2;
			dim = (len_max == diag.y) ? 1 : dim;

			float max_bound_value, min_bound_value;

			// find the range of the max and min repective to axis;
			if (dim == 0)
			{
				max_bound_value = cbound.max.x;
				min_bound_value = cbound.min.x;
			}
			else if (dim == 1)
			{
				max_bound_value = cbound.max.y;
				min_bound_value = cbound.min.y;
			}
			else
			{
				max_bound_value = cbound.max.z;
				min_bound_value = cbound.min.z;
			}

			// create two vector to store primitives in left and right node;
			std::vector<Primitive*> left, right;

			switch (BVH::splitMethod)
			{
			case BVH::SplitMethod::Middle:
			{
				float split_axis_mid = (max_bound_value + min_bound_value) / 2.0f;

				// check if min and max of split axis is same,
				// then return node containing primitives;

				if (min_bound_value == max_bound_value)
				{
					for (size_t i = start; i < end; i++)
					{
						leaf_pri.push_back(primitives[i]);
					}
					node->InitLeaf(bounds, leaf_pri);
					return node;
				}

				// iterate through primitives and based on dim split the primitives into
				// left and right;

				for (size_t i = start; i < end; i++)
				{
					if (dim == 0)
					{
						float pi_x = primitives[i]->getBounds().center.x;
						if (pi_x < split_axis_mid) { left.push_back(primitives[i]); }
						else { right.push_back(primitives[i]); }
					}
					if (dim == 1)
					{
						float pi_y = primitives[i]->getBounds().center.y;
						if (pi_y < split_axis_mid) { left.push_back(primitives[i]); }
						else { right.push_back(primitives[i]); }
					}
					if (dim == 2)
					{
						float pi_z = primitives[i]->getBounds().center.z;
						if (pi_z < split_axis_mid) { left.push_back(primitives[i]); }
						else { right.push_back(primitives[i]); }
					}
				}
				break;
			}

			default:
				const int nBuckets = 4; // number of bins
				BucketInfo buckets[nBuckets];

				// Initialize _BucketInfo_ for SAH partition buckets
				for (size_t i = start; i < end; ++i)
				{
					int b;
					if (dim == 0)
					{
						b = nBuckets * Offset(primitives[i]->getBounds().center, cbound).x;
					}
					else if (dim == 1)
					{
						b = nBuckets * Offset(primitives[i]->getBounds().center, cbound).y;
					}
					else
					{
						b = nBuckets * Offset(primitives[i]->getBounds().center, cbound).z;
					}

					if (b == nBuckets) { b = nBuckets - 1; }
					buckets[b].count++;
					buckets[b].bucketBounds.extend(primitives[i]->getBounds());
				}

				// Compute costs for splitting after each bucket
				float cost[nBuckets - 1];
				for (int i = 0; i < nBuckets - 1; ++i) {
					BBox b0 = b0.empty();
					BBox b1 = b1.empty();

					int count0 = 0, count1 = 0;
					for (int j = 0; j <= i; ++j) {
						b0.extend(buckets[j].bucketBounds);
						count0 += buckets[j].count;
					}
					for (int j = i + 1; j < nBuckets; ++j) {
						b1.extend(buckets[j].bucketBounds);
						count1 += buckets[j].count;
					}
					cost[i] = 1 + (count0 * b0.area() + count1 * b1.area()) / bounds.area();
				}

				// Find bucket to split at that minimizes SAH metric
				float minCost = cost[0];
				int minCostSplitBucket = 0;
				for (int i = 1; i < nBuckets - 1; ++i) {
					if (cost[i] < minCost) {
						minCost = cost[i];
						minCostSplitBucket = i;
					}
				}
				/*std::cout << minCost << std::endl;*/
				if ((nPrimitives > 2) || (minCost <= nPrimitives))
				{
					for (size_t i = start; i < end; i++)
					{
						int b;
						if (dim == 0)
						{
							b = nBuckets * Offset(primitives[i]->getBounds().center, cbound).x;
							if (b <= minCostSplitBucket) { left.push_back(primitives[i]); }
							else { right.push_back(primitives[i]); }
						}
						else if (dim == 1)
						{
							b = nBuckets * Offset(primitives[i]->getBounds().center, cbound).y;
							if (b <= minCostSplitBucket) { left.push_back(primitives[i]); }
							else { right.push_back(primitives[i]); }
						}
						else
						{
							b = nBuckets * Offset(primitives[i]->getBounds().center, cbound).z;
							if (b <= minCostSplitBucket) { left.push_back(primitives[i]); }
							else { right.push_back(primitives[i]); }
						}
					}
				}
				
				else
				{
					for (size_t i = start; i < end; i++)
					{
						leaf_pri.push_back(primitives[i]);
					}
					node->InitLeaf(bounds, leaf_pri);
					return node;
				}

				break;
			}

			node->InitInterior(dim,
				recursiveBuild(primitiveInfo, start, left.size(), totalNodes, orderedPrims, left),
				recursiveBuild(primitiveInfo, start, right.size(), totalNodes, orderedPrims, right));
			return node;
		}
		else
		{
			for (size_t i = start; i < end; i++)
			{
				leaf_pri.push_back(primitives[i]);
			}
			node->InitLeaf(bounds, leaf_pri);
			return node;
		}
	}

	void BVH::rebuildIndex() {

		if (primitives.empty()) return;

		// Initialize _primitiveInfo_ array for primitives
		std::vector<BVHPrimitiveInfo> primitiveInfo(primitives.size());
		for (size_t i = 0; i < primitives.size(); ++i)
			primitiveInfo[i] = { i, primitives[i]->getBounds() };

		//build the tree:
		int totalNodes = 0;

		std::vector<Primitive*> orderedPrims;
		orderedPrims.reserve(primitives.size());

		root = recursiveBuild(primitiveInfo, 0, primitives.size(),
			&totalNodes, orderedPrims, primitives);

		primitives.swap(orderedPrims);
		primitiveInfo.resize(0);

		//std::cout << "Total Nodes = " << totalNodes << std::endl;
		//std::cout << "Total Primitives = " << root->nPrimitives << std::endl;
		std::cout << "BVH created with: " << totalNodes << " nodes for: " << (int)primitives.size()
			<< " primitives: " << float(totalNodes * sizeof(LinearBVHNode)) / (1024.f * 1024.f) << std::endl;

		//nodes = (LinearBVHNode*)malloc(sizeof(totalNodes)); // , 64);
		//int offset = 0;
		//flattenBVHTree(root, &offset); 
	}

	BBox BVH::getBounds() const {
		return this->root->bounds;
	}

	int BVH::flattenBVHTree(BVHBuildNode* root, int* offset) {
		LinearBVHNode* linearNode = &nodes[*offset];
		linearNode->bounds = root->bounds;

		int myOffset = (*offset)++;

		if (root->nPrimitives > 0) {
			linearNode->primitivesOffset = root->firstPrimOffset;
			linearNode->nPrimitives = root->nPrimitives;
		}
		else {
			// Create interior flattened BVH node
			linearNode->axis = root->splitAxis;
			linearNode->nPrimitives = 0;
			flattenBVHTree(root->children[0], offset);
			linearNode->secondChildOffset =
				flattenBVHTree(root->children[1], offset);
		}
		return myOffset;
	}

	Intersection NodeIntersect(const Ray& ray, float pbd, const BVHBuildNode* root, const LinearBVHNode* nodes, std::vector<Primitive*> primitives)
	{
        Intersection result = Intersection::failure();

        // Does the ray intersect with the world?
        std::pair<float,float> dists = root->bounds.intersect(ray);
        float t1 = dists.first;
        float t2 = dists.second;
        if(t1 > t2){
            // nope
            return result;
        }

        // create the stack with the root inside to begin
        std::vector<const BVHBuildNode*> remainingNodes;
        remainingNodes.push_back(root);
        const BVHBuildNode *currentNode;
        Intersection temp;
		
		#pragma omp parallel
        while(!remainingNodes.empty()){
            // Intersec with last node from stack, delete it from stack
            currentNode = remainingNodes.back();
            remainingNodes.pop_back();
            // If current node does not have any childs, we intersec with its primitives
            if (currentNode->nPrimitives != 0)
			{
                // std::cout << "->Leaf found" << std::endl;
				//#pragma omp parallel for collapse(2) schedule(dynamic)
				for (auto p : currentNode->pri) 
				{
                //for(int i = 0; i < currentNode->nPrimitives; i++) {
                    temp = p->intersect(ray, pbd);
                    if (temp && temp.distance < pbd){
                        pbd = temp.distance;
                        result = temp;
                    }
                }
            } else {
                //We intersec with its childs and add them to the stack if they succed

                // Intersec with left child
                dists = currentNode->children[0]->bounds.intersect(ray);
                t1 = dists.first;
                t2 = dists.second;
                if (t1 <= t2) {
                    // std::cout << "-->leftChild added to stack" << std::endl;
                    remainingNodes.push_back(currentNode->children[0]);
                }

                // Intersec with right child
                dists = currentNode->children[1]->bounds.intersect(ray);
                t1 = dists.first;
                t2 = dists.second;
                if (t1 <= t2) {
                    // std::cout << "-->rightChild added to stack" << std::endl;
                    remainingNodes.push_back(currentNode->children[1]);
                }
            }
        }
        return result;

		Intersection hit = Intersection::failure();
		Intersection curr_obj = Intersection::failure();

		// leaf nodes
		//if (root->nPrimitives != 0)
		//{
		//	Intersection curr_obj = Intersection::failure();

		//	for (int i = 0; i < root->nPrimitives; i++)
		//	{
		//		curr_obj = primitives[root->firstPrimOffset + i]->intersect(ray, pbd);

		//		if (curr_obj && (curr_obj.distance < pbd))
		//		{
		//			hit = curr_obj;
		//			pbd = hit.distance;
		//		}
		//	}

		//	return hit;
		//}
		//// internal nodes
		//else
		//{
		//	std::pair<float, float> left = root->children[0]->bounds.intersect(ray);
		//	std::pair<float, float> right = root->children[1]->bounds.intersect(ray);

		//	if (left.first <= left.second)
		//	{
		//		Intersection curr_intersection = NodeIntersect(ray, pbd, root->children[0], nodes, primitives);
		//		if (curr_intersection && curr_intersection.distance < pbd)
		//		{
		//			pbd = curr_intersection.distance;
		//			hit = curr_intersection;
		//		}
		//	}

		//	if (right.first <= right.second)
		//	{
		//		Intersection curr_intersection = NodeIntersect(ray, pbd, root->children[1], nodes, primitives);
		//		if (curr_intersection && curr_intersection.distance < pbd)
		//		{
		//			pbd = curr_intersection.distance;
		//			hit = curr_intersection;
		//		}
		//	}

		//	return hit;
		//}

	}

	Intersection BVH::intersect(const Ray& ray, float previousBestDistance) const {
		Intersection primitive_hit = Intersection::failure();

		primitive_hit = NodeIntersect(ray, previousBestDistance, this->root, nodes, primitives);

		return primitive_hit;
	}

	void BVH::add(Primitive* p) {
		this->primitives.push_back(p);
	}

	void BVH::setMaterial(Material* m) {

		for (auto primitive : primitives)
		{
			primitive->setMaterial(m);
		}
	}

	void BVH::setCoordMapper(CoordMapper* cm) {

		for (auto primitive : primitives)
		{
			primitive->setCoordMapper(cm);
		}

	}

	void BVH::serialize(BVH::Output& output) {
		// To implement this function:
		// - Call output.setNodeCount() with the number of nodes in the BVH
		/* TODO */
		// - Set the root node index using output.setRootId()
		/* TODO */
		// - Write each and every one of the BVH nodes to the output using output.writeNode()
		/* TODO */ NOT_IMPLEMENTED;
	}
	void BVH::deserialize(BVH::Input& input) {
		// To implement this function:
		// - Allocate and initialize input.getNodeCount() nodes
		/* TODO */
		// - Fill your nodes with input.readNode(index)
		/* TODO */
		// - Use the node at index input.getRootId() as the root node
		/* TODO */ NOT_IMPLEMENTED;
	}
}