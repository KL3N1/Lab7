public class CardPayment extends PaymentMethod {
    @Override
    public void processPayment(float amount) {
        System.out.printf("Оплата картой: %.2f%n", amount);
    }
}