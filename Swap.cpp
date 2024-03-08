#include "Swap.h"

Swap::Swap(const InstrumentDescription& instrument):
        fixedPayerLeg(instrument.payer, zeroCouponCurve),
        floatingPayerLeg(instrument.payer, zeroCouponCurve),
        fixedReceiverLeg(instrument.receiver, zeroCouponCurve),
        floatingReceiverLeg(instrument.receiver, zeroCouponCurve),
        isPayerFixed(instrument.payer.type == LegDescription::FIXED),
        isReceiverFixed(instrument.receiver.type == LegDescription::FIXED) {}

double Swap::price() const {
    double payerLegPrice = isPayerFixed ? fixedPayerLeg.price() : floatingPayerLeg.price();
    double receiverLegPrice = isReceiverFixed ? fixedReceiverLeg.price() : floatingReceiverLeg.price();
    double swapPrice = payerLegPrice - receiverLegPrice;

    if (swapPrice > 0) {
        std::cout << "Tenemos que pagar: " << swapPrice << std::endl;
    } else if (swapPrice < 0) {
        std::cout << "Tenemos que recibir: " << -swapPrice << std::endl;
    } else {
        std::cout << "El valor del swap es cero, no hay pago ni recepción." << std::endl;
    }

    return swapPrice;
}
