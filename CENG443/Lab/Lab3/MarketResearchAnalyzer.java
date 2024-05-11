import java.io.*;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.*;
import java.util.function.Function;
import java.util.stream.Collectors;

class MarketResearchAnalyzer {

    public static void function1(List<Data> datas) {
        int sum = datas.stream()
                .filter(data -> data.name.startsWith("A"))
                .mapToInt(Data::findPurchasedProduct)
                .reduce(0, (x, y) -> x + y);

        System.out.println(sum);
    }

    public static void function2(List<Data> datas) {
        double maxPrice = datas.stream()
                .mapToDouble(Data::findMostExpensiveProduct)
                .reduce(0, Double::max);

        System.out.println(maxPrice);
    }

    public static void function3(List<Data> datas) {
        String highestPaidEntry = datas.stream()
                .reduce(Data::findHighestPurchase)
                .map(data -> data.date)
                .orElse(null);

        System.out.println(highestPaidEntry);
    }

    public static void function4(List<Data> datas) {
        Map<String, Integer> productPurchaseCounts = new HashMap<>();

        datas.stream()
                .filter(data -> data.date.startsWith("19"))
                .forEach(data -> {
                    for (int i = 0; i < 5; i++) {
                        productPurchaseCounts.merge(Data.mapKeyToProduct(i), data.numList.get(i), Integer::sum);
                    }
                });

        Map.Entry<String, Integer> mostPopularProductEntry = productPurchaseCounts.entrySet().stream()
                .reduce((entry1, entry2) -> entry1.getValue() > entry2.getValue() ? entry1 : entry2)
                .orElse(null);

        System.out.println(mostPopularProductEntry.getKey());
    }

    public static void function5(List<Data> datas) {
        Map<String, Integer> productPurchaseCounts = new HashMap<>();

        datas.stream()
                .filter(data -> data.date.startsWith("20"))
                .forEach(data -> {
                    for (int i = 0; i < 5; i++) {
                        productPurchaseCounts.merge(Data.mapKeyToProduct(i), data.numList.get(i), Integer::sum);
                    }
                });

        String leastPopularProductEntry = productPurchaseCounts.entrySet().stream()
                .reduce((entry1, entry2) -> entry1.getValue() < entry2.getValue() ? entry1 : entry2)
                .get()
                .getKey();

        System.out.println(leastPopularProductEntry);
    }

    public static void function6(List<Data> datas) {
        Map<String, Integer> productPurchaseCounts = new HashMap<>();
        Map<String, Integer> totalAgeOfProductPurchase = new HashMap<>();
        Map<String, Double> averageAgeOfProductPurchase = new HashMap<>();

        datas.stream().forEach(data -> {
            for (int i = 0; i < 5; i++) {
                productPurchaseCounts.merge(Data.mapKeyToProduct(i), data.numList.get(i), Integer::sum);
                totalAgeOfProductPurchase.merge(Data.mapKeyToProduct(i), data.numList.get(i) * data.age, Integer::sum);
            }
        });

        totalAgeOfProductPurchase.forEach((name, totalAge) -> {
            double averageAge = totalAge / productPurchaseCounts.get(name);
            averageAgeOfProductPurchase.put(name, averageAge);
        });

        String popularAmongTeens = averageAgeOfProductPurchase.entrySet().stream()
                .reduce((entry1, entry2) -> entry1.getValue() < entry2.getValue() ? entry1 : entry2)
                .get()
                .getKey();

        System.out.println(popularAmongTeens);
    }

    public static void function7(List<Data> datas) {
        Map<String, Map.Entry<String, Double>> oldestPurchase = new HashMap<>();
        Map<String, Map.Entry<String, Double>> newestPurchase = new HashMap<>();
        Map<String, Double> inflated = new HashMap<>();

        datas.stream().forEach(data -> {
            for (int i = 0; i < 5; i++) {
                if (data.numList.get(i) != 0) {
                    oldestPurchase.merge(Data.mapKeyToProduct(i), Map.entry(data.date, data.priceList.get(i)),
                            Data::compareDatesForOlder);
                    newestPurchase.merge(Data.mapKeyToProduct(i), Map.entry(data.date, data.priceList.get(i)),
                            Data::compareDatesForNewer);
                }
            }
        });

        oldestPurchase.forEach((name, product) -> {
            double inf = (newestPurchase.get(name).getValue() - product.getValue()) /
                    product.getValue();
            inflated.put(name, inf);
        });

        String mostInflatedProduct = inflated.entrySet().stream()
                .reduce((entry1, entry2) -> entry1.getValue() > entry2.getValue() ? entry1 : entry2)
                .get()
                .getKey();

        System.out.println(mostInflatedProduct);
    }

    public static void main(String[] args) throws FileNotFoundException {
        String inputFile = args[0];
        int questionNumber = Integer.parseInt(args[1]);

        BufferedReader br = new BufferedReader(new InputStreamReader(new FileInputStream(new File(inputFile))));

        Function<String, Data> mapToData = (line) -> {
            String[] fields = line.split(",", -1);
            List<Integer> numList = new ArrayList<>();
            List<Double> priceList = new ArrayList<>();

            String name = fields[0];
            int age = Integer.parseInt(fields[1]);
            String date = fields[2];

            for (int i = 3; i < fields.length; i += 2) {
                if (!fields[i].isEmpty()) {
                    priceList.add(Double.parseDouble(fields[i]));
                } else {
                    priceList.add(0.0);
                }
                if (!fields[i + 1].isEmpty()) {
                    numList.add(Integer.parseInt(fields[i + 1]));
                } else {
                    numList.add(0);
                }
            }

            return new Data(name, age, date, priceList, numList);
        };
        List<Data> datas = new ArrayList<>();
        try {
            datas = Files.lines(Paths.get(inputFile)).skip(1).map(mapToData).collect(Collectors.toList());
        } catch (Exception e) {
        }

        switch (questionNumber) {
            case 1:
                function1(datas);
                break;
            case 2:
                function2(datas);
                break;
            case 3:
                function3(datas);
                break;
            case 4:
                function4(datas);
                break;
            case 5:
                function5(datas);
                break;
            case 6:
                function6(datas);
                break;
            case 7:
                function7(datas);
                break;
        }
    }
}
