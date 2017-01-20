#ifndef INTERFACE_H
#define INTERFACE_H

#define REGISTER_SERVANT(servant, class_name)	\
	class_name cn = NEW class_name(); 	\
	servant_register(servant, cn::execute);

#endif 	// INTERFACE_H