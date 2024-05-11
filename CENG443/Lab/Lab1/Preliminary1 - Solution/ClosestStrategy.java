import java.util.List;

public class ClosestStrategy extends Strategy {
    private Store prev;
    @Override
    public String getStrategyType() {
        return "Cl";
    }

    @Override
    public void setNextTarget(Customer c, List<Store> StoreList) {
        double closest = Double.POSITIVE_INFINITY;
        for (Store s : StoreList) {
            if (s.getProductType() == c.getShoppingList().get(0).getProductType() &&  s != prev) {
                double dist = c.getPosition().distanceTo(s.getPosition());
                if (dist < closest) {
                    closest = dist;
                    target = s;
                }
            }
        }
    }

    @Override
    public void tryToBuy(Customer c) {
        try {
            target.sell();
            c.getShoppingList().remove(0);
        } catch (IllegalStateException e) {
            prev = target;
        }
        target = null;
    }
}
