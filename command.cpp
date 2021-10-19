#include "command.h"

Command::Command(const std::string& name)
: m_name(name) 
{
}

void Command::printContent(std::ostream& out) const
{
    out << m_name;
}