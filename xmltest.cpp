#ifdef TIXML_USE_STL
	#include <iostream>
	#include <sstream>
	using namespace std;
#else
	#include <stdio.h>
#endif

#if defined( WIN32 ) && defined( TUNE )
	#include <crtdbg.h>
	_CrtMemState startMemState;
	_CrtMemState endMemState;
#endif

#include "tinyxml.h"
int delete_null_ele(TiXmlDocument *p_dom)
{
	TiXmlElement *win = NULL;
	TiXmlHandle docHandle(p_dom);
	TiXmlElement *item = docHandle.FirstChildElement("MyApp").FirstChildElement("Windows").ToElement();
	while (NULL != item){
		win = item->FirstChildElement("Window");
		while (NULL != win){
			//printf("delete_null_ele Attribute RegexText is <%s>\n", col->Attribute("RegexText"));
			if (0 == strlen(win->Attribute("name"))){
				item->RemoveChild(win);
			}
			win = win->NextSiblingElement("Window");
		}
		if (NULL == item->FirstChildElement()){
			item->Parent()->RemoveChild(item);
		}
		item = item->NextSiblingElement("Windows");
	}
	return 0;

	
}
int delete_comment(TiXmlDocument *p_dom)
{
	int type = 0;
	TiXmlNode *node   = NULL;
	TiXmlNode *parent = NULL;
	TiXmlNode *root = NULL;

	node = p_dom->FirstChild();
	if (NULL == node){
		printf("delete_comment: node is NULL\n");
		return -1;
	}
	type = node->Type();
	parent = node->Parent();
	root = parent;


	TiXmlNode *tmp_parent = NULL;
	while (1){
		if (TiXmlNode::TINYXML_COMMENT == type){
	//		printf("comment is %s\n",node->Value());
			parent->RemoveChild(node);
		}
		tmp_parent = node;
		node = node->FirstChild();
		if (NULL == node){/*have no child*/
			node = tmp_parent->NextSibling();
			if (NULL == node){
				while (parent != root){
					node = parent->NextSibling();
					parent = parent->Parent();	
					if (NULL != node){
						break;
					}
				}
				if(parent == root){
					printf("perfect ending\n");
					return 0;
				}
			}
		}else{/*have at least one child*/
			parent = node->Parent();
		}
		type = node->Type();
	}

	return -1;
	
}

int print_xml(void)
{

	TiXmlDocument dom("demo.xml");
	dom.LoadFile();
	delete_comment(&dom);
	delete_null_ele(&dom);
	//dom.Print();
	dom.SaveFile("demo.xml.bak");
	return 0;
}

int main()
{
	print_xml();
	return 0;
}

