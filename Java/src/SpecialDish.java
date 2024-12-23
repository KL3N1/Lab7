public class SpecialDish extends Dish {
    private String specialIngredient;

    public SpecialDish(String name, float price, int quantity, String specialIngredient) {
        super(name, price, quantity);
        this.specialIngredient = specialIngredient;
    }

    @Override
    public void print() {
        super.print();
        System.out.printf("Специальный ингредиент: %s%n", specialIngredient);
    }

    @Override
    public float calculateDiscountedPrice() {
        return price * 0.9f; // 10% скидка на специальное блюдо
    }

    @Override
    public String toString() {
        return super.toString() + ", Специальный ингредиент: " + specialIngredient;
    }
}