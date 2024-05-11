import java.util.List;

public class CheapestStrategy extends Strategy {
    @Override
    public String getStrategyType() {
        return "Ch";
    }

    @Override
    public void setNextTarget(Customer c, List<Store> storeList) {
        int cheapest = Integer.MAX_VALUE;
        for (Store s : storeList) {
            if (s.getProductType() == c.getShoppingList().get(0).getProductType() && s.getPrice() < cheapest) {
                cheapest = s.getPrice();
                target = s;
            }
        }
    }

    @Override
    public void tryToBuy(Customer c) {
        try {
            target.sell();
            c.getShoppingList().remove(0);
            target = null;
        } catch (IllegalStateException e) {
        }
    }


}
