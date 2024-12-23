public class DataHolder<T> {
    private T data;

    public DataHolder(T data) {
        this.data = data;
    }

    public void print() {
        System.out.println("Значение: " + data);
    }
}