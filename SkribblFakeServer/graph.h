#include"node.h"
#include<vector>
#include<string>
#include<tuple>
namespace skribbl
{
	class Graph
	{
		std::vector<std::pair<std::vector<Node*>,std::tuple<std::string,std::string,std::string>>> nodes;

	public:
		Graph()=default;
		std::vector<std::pair<std::vector<Node*>,std::tuple<std::string, std::string, std::string>>> getNodes() {
			return nodes;
		}
		void addNodes(std::pair<std::vector<Node*>,std::tuple< std::string, std::string, std::string>> n) {
			nodes.push_back(n);
		}
		void clear()
		{
			for (std::pair<std::vector<Node*>, std::tuple<std::string, std::string, std::string>> i : nodes)
				for (Node* j : i.first)
				{
					delete j;
				}
			nodes.clear();
		}

		void deletelast()
		{
			if (nodes.empty())
			{
				return;
			}
			for (Node* i : nodes.back().first)
			{
				delete i;
			}
			if (!nodes.empty())
				nodes.pop_back();

		}

		~Graph()
		{
			for (std::pair<std::vector<Node*>,std::tuple<std::string,std::string,std::string>> i : nodes)
				for (Node* j : i.first)
				{
					delete j;
				}
			nodes.clear();
		}

	};
}

