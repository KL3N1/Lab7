public class Dish implements Printable {
    protected String name;
    protected float price;
    protected int quantity;

    public Dish(String name, float price, int quantity) {
        this.name = name;
        this.price = price;
        this.quantity = quantity;
    }

    @Override
    public void print() {
        System.out.printf("Блюдо: %s, Цена: %.2f, Количество: %d%n", name, price, quantity);
    }

    public float getPrice() {
        return price;
    }

    public int getQuantity() {
        return quantity;
    }

    public String getName() {
        return name;
    }

    public float calculateDiscountedPrice() {
        return price;
    }

    @Override
    public String toString() {
        return String.format("Блюдо: %s, Цена: %.2f, Количество: %d", name, price, quantity);
    }
}