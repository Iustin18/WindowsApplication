#include "oferta.h"

bool cmpDenumire(const oferta& o1, const oferta& o2) {
	return o1.getDenumire() < o2.getDenumire();
}

bool cmpDenumireD(const oferta& o1, const oferta& o2) {
	return o1.getDenumire() > o2.getDenumire();
}

bool cmpDestinatie(const oferta& o1, const oferta& o2) {
	return o1.getDestinatie() < o2.getDestinatie();
}

bool cmpDestinatieD(const oferta& o1, const oferta& o2) {
	return o1.getDestinatie() > o2.getDestinatie();
}

bool cmpTip(const oferta& o1, const oferta& o2) {
	return o1.getTip() < o2.getTip();
}

bool cmpTipD(const oferta& o1, const oferta& o2) {
	return o1.getTip() > o2.getTip();
}

bool cmpPret(const oferta& o1, const oferta& o2) noexcept {
	return o1.getPret() < o2.getPret();
}

bool cmpPretD(const oferta& o1, const oferta& o2) noexcept {
	return o1.getPret() > o2.getPret();
}

