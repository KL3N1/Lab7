public class CashPayment extends PaymentMethod {
    @Override
    public void processPayment(float amount) {
        System.out.printf("Оплата наличными: %.2f%n", amount);
    }
}