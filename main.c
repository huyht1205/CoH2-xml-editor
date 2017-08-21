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

#define TARGET	"assault_pioneer_mp.xml"

const char *increasex10List[100] = {
	"hitpoints", "armor", "rear_armor", "regeneration",
	"tp_global", "outer_radius",
	NULL};

const char *increasex2List[100] = {
	"acceleration", "deceleration", "rotation_rate", "speed_max",
	NULL
};

const char *decreaseList[100] = {
	"fuel", "manpower", "munition", "time_seconds",
	"personnel_pop",
	NULL
};

#define DECREASE	(-1)
#define INCREASEx10	(10)
#define INCREASEx2	(2)

/**
 * print_element_names:
 * @a_node: the initial xml node to consider.
 *
 * Prints the names of the all the xml elements
 * that are siblings or children of a given xml node.
 */
static void
print_element_names(xmlNode * a_node)
{
	xmlNode *cur_node = NULL;

	for (cur_node = a_node; cur_node; cur_node = cur_node->next) {

		if (cur_node->properties && cur_node->properties->next) {

			char *nameProp = (char *) cur_node->properties->children->content;
			char *valueProp = (char *) cur_node->properties->next->children->content;
			int changeType = 0;
			float value = 0;

			// Increase 10
			for (int i = 0; NULL != increasex10List[i]; i++) {
				if (0 == strcmp(nameProp, increasex10List[i])) {
					changeType = INCREASEx10;
					goto FINISHED_CHECK_CHANGE;
				} else {}
			}

			// Increase 2
			for (int i = 0; NULL != increasex2List[i]; i++) {
				if (0 == strcmp(nameProp, increasex2List[i])) {
					changeType = INCREASEx2;
					goto FINISHED_CHECK_CHANGE;
				} else {}
			}

			//Decrease
			for (int i = 0; NULL != decreaseList[i]; i++) {
				if (0 == strcmp(nameProp, decreaseList[i])) {
					changeType = DECREASE;
					goto FINISHED_CHECK_CHANGE;
				} else {}
			}
FINISHED_CHECK_CHANGE:
			if (changeType) {
				printf("\t%s = %s -> ", nameProp, valueProp);
				sscanf(valueProp, "%f", &value);
				switch (changeType) {
					case INCREASEx10:
					case INCREASEx2:

						if (0 == value) {
							value = 10;
						} else if (0 <= value) {
							value *= changeType;
						} else {}
						break;

					case DECREASE:
						if (10 >= value && 0 != value) {
							value = 1;
						} else {
							value /= 10;
						}

					default:
						break;
				}
				sprintf(valueProp, "%d", (int) value);
				printf("%s\n", valueProp);
			} else {}
		}
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
