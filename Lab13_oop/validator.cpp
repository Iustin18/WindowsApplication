#include "validator.h"
#include <assert.h>
#include <sstream>
using std::stringstream;

void ofertaValidator::validate(const oferta& o) {
	vector<string> msgs;
	if (o.getPret() < 0) msgs.push_back("pret negativ");
	if (o.getDenumire().size() <= 0) msgs.push_back("denumire vida");
	if (o.getDestinatie().size() <= 0) msgs.push_back("destinatie vida");
	if (o.getTip().size() <= 0) msgs.push_back("tip vid");
	if (msgs.size() > 0) {
		throw ValidateException(msgs);
	}
}

ostream& operator<<(ostream& out, const ValidateException& ex) {
	for (const auto& msg : ex.msgs) {
		out << msg << " ";
	}
	return out;
}

void testValidator() {
	ofertaValidator v;
	oferta o{ "","","b",-1 };
	try {
		v.validate(o);
	}
	catch (const ValidateException & ex) {
		stringstream sout;
		sout << ex;
		const auto mesaj = sout.str();
		assert(mesaj.find("vida") >= 0);
		assert(mesaj.find("vid") >= 0);
		assert(mesaj.find("negativ") >= 0);
	}
}