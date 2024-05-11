import java.util.*;

class Data {
    String name;
    int age;
    String date;
    List<Integer> numList = new ArrayList<>();
    List<Double> priceList = new ArrayList<>();

    Data(String name, int age, String date, List<Double> priceList, List<Integer> numList) {
        this.name = name;
        this.age = age;
        this.date = date;
        this.priceList = priceList;
        this.numList = numList;
    }

    static public String mapKeyToProduct(int key) {
        switch (key) {
            case 0:
                return "A";
            case 1:
                return "B";
            case 2:
                return "C";
            case 3:
                return "D";
            case 4:
                return "E";
            default:
                return "";
        }
    }

    public static int findPurchasedProduct(Data data) {
        int sum = 0;
        for (int i = 0; i < data.numList.size(); i++) {
            sum += data.numList.get(i);
        }
        return sum;
    }

    public static double findMostExpensiveProduct(Data data) {
        double max = 0;
        for (int i = 0; i < data.priceList.size(); i++) {
            max = Math.max(max, data.priceList.get(i));
        }
        return max;
    }

    public static Data findHighestPurchase(Data data1, Data data2) {
        double sum1 = 0, sum2 = 0;
        for (int i = 0; i < data1.numList.size(); i++) {
            sum1 += data1.numList.get(i) * data1.priceList.get(i);
            sum2 += data2.numList.get(i) * data2.priceList.get(i);

        }
        return sum1 > sum2 ? data1 : data2;
    }

    public static Map.Entry<String, Double> compareDatesForOlder(Map.Entry<String, Double> entry1,
            Map.Entry<String, Double> entry2) {
        int result = entry1.getKey().compareTo(entry2.getKey());
        return result < 0 ? entry1 : entry2;
    }

    public static Map.Entry<String, Double> compareDatesForNewer(Map.Entry<String, Double> entry1,
            Map.Entry<String, Double> entry2) {
        int result = entry1.getKey().compareTo(entry2.getKey());
        return result > 0 ? entry1 : entry2;
    }
}