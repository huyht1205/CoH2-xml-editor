/**
 * section: Parsing
 * synopsis: Parse an XML file to a tree and free it
 * purpose: Demonstrate the use of xmlReadFile() to read an XML file
 *          into a tree and and xmlFreeDoc() to free the resulting tree
 * usage: parse1 test1.xml
 * test: parse1 test1.xml
 * author: Daniel Veillard
 * copy: see Copyright for the status of this software.
 */

#include <stdio.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <string.h>
#include <libxml/xmlmemory.h>
#include <libxml/xpath.h>

#include "utils.h"

#define TARGET	"assault_pioneer_mp.xml"

/**
 * print_element_names:
 * @root: the initial xml node to consider.
 *
 * Prints the names of the all the xml elements
 * that are siblings or children of a given xml node.
 */
static void
print_element_names(xmlNode * root)
{
	xmlNode *cur_node = NULL;
	char *propName = NULL;

	for (cur_node = root; cur_node; cur_node = cur_node->next) {
		if (cur_node->properties) {
			propName = get_properties_name(cur_node->properties);

			if (0 == strcmp(propName, "accuracy")) {
				printf("Acc: far=%s, mid=%s, near=%s\n",
				get_properties_value(cur_node->properties->next);
				get_properties_value(cur_node->properties->next->next);
			} else {}

		} else {}
		/*
		if (0 == strcmp((char *)cur_node->name, "accuracy")) {

			char *far = (char *) cur_node->properties->children->content;
			char *mid = (char *) cur_node->properties->next->children->content;
			char *near = (char *) cur_node->properties->next->next->children->content;
			printf("Acc: far=%s, mid=%s, near=%s\n", far, mid, near);
		} else {}
		*/
		print_element_names(cur_node->children);
	}
}

int main(int argc, char **argv) {
	/*
	 * this initialize the library and check potential ABI mismatches
	 * between the version it was compiled for and the actual shared
	 * library used.
	 */
	LIBXML_TEST_VERSION

	char *fileName = argv[1];

	if (NULL == fileName) {
		fileName = TARGET;
	} else {}

	printf("%s\n", fileName);
	xmlDocPtr doc = xmlParseFile(fileName);
	if (doc) {
		xmlNodePtr root = xmlDocGetRootElement(doc);

		print_element_names(root);

		xmlSaveFile(fileName, doc);
	} else {}

	/*
	 * Cleanup function for the XML library.
	 */
	xmlCleanupParser();

	return(0);
}
