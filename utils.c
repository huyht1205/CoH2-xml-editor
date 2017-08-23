#include <libxml/tree.h>
#include <assert.h>

#include "utils.h"

char *get_properties_name(xmlAttrPtr aProperty)
{
	assert(NULL != aProperty);

	return (char *) aProperty->children->content; 
}

char *get_properties_value(xmlAttrPtr aProperty)
{
	assert(NULL != aProperty);

	return (char *) aProperty->next->children->content; 
}
