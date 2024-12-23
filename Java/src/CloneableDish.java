public class CloneableDish extends Dish implements Cloneable {
    public CloneableDish(String name, float price, int quantity) {
        super(name, price, quantity);
    }

    @Override
    protected Object clone() throws CloneNotSupportedException {
        return super.clone();
    }

    public CloneableDish deepClone() {
        CloneableDish clone = null;
        try {
            clone = (CloneableDish) super.clone();
            clone.name = new String(this.name);
        } catch (CloneNotSupportedException e) {
            e.printStackTrace();
        }
        return clone;
    }
}