import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.List;

public class Menu {
    private List<Dish> dishes;

    public Menu() {
        dishes = new ArrayList<>();
    }

    public void addDish(Dish dish) {
        if (dishes.size() < 10) {
            dishes.add(dish);
        } else {
            System.out.println("Меню переполнено!");
        }
    }

    public void print() {
        System.out.println("Меню:");
        for (Dish dish : dishes) {
            System.out.println(dish);
        }
        System.out.println();
    }

    public Dish getDish(int index) {
        if (index >= 0 && index < dishes.size()) {
            return dishes.get(index);
        }
        return null;
    }

    public int getDishCount() {
        return dishes.size();
    }

    // Сортировка блюд по цене
    public void sortDishesByPrice() {
        Collections.sort(dishes, Comparator.comparing(Dish::getPrice));
    }

    // Поиск блюда по имени
    public Dish findDishByName(String name) {
        for (Dish dish : dishes) {
            if (dish.getName().equals(name)) {
                return dish;
            }
        }
        return null;
    }

}