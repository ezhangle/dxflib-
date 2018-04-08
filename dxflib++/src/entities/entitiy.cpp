#include "dxflib++/include/entities/entity.h"
#include "dxflib++/include/utilities.h"

dxflib::entity_buffer_base::~entity_buffer_base()
= default;

/**
 * \brief Parse function for the base class for entity buffers
 * \param cl Current line
 * \param nl Next line
 * \return status -> 1: sucess, 0: failure
 */
int dxflib::entity_buffer_base::parse(const std::string& cl, const std::string& nl)
{
	using namespace group_codes;
	// Group code conversion
	int code{-1};
	try
	{
		if (utilities::is_number(cl))
			code = std::stoi(cl);
	}
	catch(std::invalid_argument&)
	{
		// if failure then set to -1
		code = -1;
	}
	catch(std::out_of_range&)
	{
		// if failure then set to -1
		code = -1;
	}

	// Switch on the code
	switch (static_cast<group_codes::entity_codes>(code))
	{
	case entity_codes::error:
		return code;
	case entity_codes::layer:
		layer = nl;
		return 1;
	case entity_codes::handle:
		handle = nl;
		return 1;
	case entity_codes::soft_pointer:
		soft_pointer = nl;
		return 1;
	default:
		return 0;
	}
}

/**
 * \brief Entity base class constructor
 * \param eb entity buffer base struct
 */
dxflib::entity::entity(entity_buffer_base& eb):
	layer(eb.layer), handle(eb.handle), soft_pointer_(eb.soft_pointer)
{

}