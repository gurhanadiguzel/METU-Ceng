package ceng.ceng351.foodrecdb;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.List;

public class FOODRECDB implements IFOODRECDB {
    
    /**
    * Place your initialization code inside if required.
    * 
    * <p>
    * This function will be called before all other operations. If your implementation
    * need initialization , necessary operations should be done inside this function. For
    * example, you can set your connection to the database server inside this function.
    */	
    Connection connection = null;
	
    public void initialize() {
	   String user = "e2448025";
	   String password = "4dOb5AHa1l71J48S";
	   String host = "momcorp.ceng.metu.edu.tr";
	   String database = "db2448025";
	   int port = 8080; 
	   
	   String url = "jdbc:mysql://" + host + ":" + port + "/" + database + "?useSSL=false";
	   
	    try {
           Class.forName("com.mysql.cj.jdbc.Driver");
           connection =  DriverManager.getConnection(url, user, password);
        } 
       catch (SQLException | ClassNotFoundException e) {
           e.printStackTrace();
        } 
    }
   
    /**
    * Should create the necessary tables when called.
    * 
    * @return the number of tables that are created successfully.
    */
    public int createTables() {
	   int addedTableCount = 0;
	   
        try{
    	   addedTableCount++;
           Statement statement = connection.createStatement();

           String menuItemQuery =  "CREATE TABLE MenuItems " + 
                                   "(itemID INTEGER ," +
                                   "itemName VARCHAR(40)," +
                                   "cuisine VARCHAR(20)," +
                                   "price INTEGER," +
                                   "PRIMARY KEY (itemID))";

           statement.executeUpdate(menuItemQuery);
        } catch (SQLException e){
    	   addedTableCount--;
    	   e.printStackTrace();
        }
        try {
    	   addedTableCount++;
    	   Statement statement = connection.createStatement();
    	   
    	   String ingredientQuery =    "CREATE TABLE Ingredients " +
                   "(ingredientID INTEGER," +
                   "ingredientName VARCHAR(40)," +
                   "PRIMARY KEY (ingredientID))";
    	   
    	   statement.executeUpdate(ingredientQuery);
        } catch(SQLException e){
    	   addedTableCount--;
    	   e.printStackTrace();
        }
        try {
    	   addedTableCount++;
    	   Statement statement = connection.createStatement();
    	   
    	   String includeQuery =  "CREATE TABLE Includes " +
                   "(itemID INTEGER ," +
                   "ingredientID INTEGER ," +
                   "PRIMARY KEY (itemID, ingredientID)," +
                   "FOREIGN KEY (itemID) REFERENCES MenuItems(itemID)," +
                   "FOREIGN KEY (ingredientID) REFERENCES Ingredients(ingredientID))";
    	   
    	   statement.executeUpdate(includeQuery);
        } catch(SQLException e){
    		   addedTableCount--;
               e.printStackTrace();
        }
       
        try {
    	   addedTableCount++;
    	   Statement statement = connection.createStatement();
    	   
           String ratingQuery =   "CREATE TABLE Ratings " +
                   "(ratingID INTEGER," +
                   "itemID INTEGER," +
                   "rating INTEGER," +
                   "ratingDate DATE," +
                   "PRIMARY KEY (ratingID)," +
                   "FOREIGN KEY (itemID) REFERENCES MenuItems(itemID))";
           
           statement.executeUpdate(ratingQuery);
        } catch(SQLException e){
    	   addedTableCount--;
    	   e.printStackTrace();
        }       
        try {
    	   addedTableCount++;
    	   Statement statement = connection.createStatement();
    	   
           String dietaryCategoryQuery =   "CREATE TABLE DietaryCategories " +
                   "(ingredientID INTEGER," +
                   "dietaryCategory VARCHAR(20)," +
                   "PRIMARY KEY (ingredientID, dietaryCategory)," +
                   "FOREIGN KEY (ingredientID) REFERENCES Ingredients(ingredientID))";
           
           statement.executeUpdate(dietaryCategoryQuery);
        } catch(SQLException e){
    	   addedTableCount--;
    	   e.printStackTrace();
        }

       return addedTableCount;
    }
   
   
   /**
    * Should drop the tables if exists when called. 
    * 
    * @return the number of tables are dropped successfully.
    */
    public int dropTables(){
        int droppedTableCount = 0 ;

        try{
            droppedTableCount++;
            Statement statement = connection.createStatement();

            String ratingQuery = "DROP TABLE Ratings";
            statement.executeUpdate(ratingQuery);
        } catch (SQLException e){
            droppedTableCount--;
        }
        try{
            droppedTableCount++;
            Statement statement = connection.createStatement();

            String dietaryCategoryQuery = "DROP TABLE DietaryCategories";
            statement.executeUpdate(dietaryCategoryQuery);
        } catch (SQLException e){
            droppedTableCount--;
        }
        try{
            droppedTableCount++;
            Statement statement = connection.createStatement();

            String includeQuery = "DROP TABLE Includes";
            statement.executeUpdate(includeQuery);
        } catch (SQLException e){
            droppedTableCount--;
        }
        try{
            droppedTableCount++;
            Statement statement = connection.createStatement();

            String menuItemQuery = "DROP TABLE MenuItems";
            statement.executeUpdate(menuItemQuery);
        } catch (SQLException e){
            droppedTableCount--;
        }
        try{
            droppedTableCount++;
            Statement statement = connection.createStatement();

            String ingredientQuery = "DROP TABLE Ingredients";
            statement.executeUpdate(ingredientQuery);
        } catch (SQLException e){
            droppedTableCount--;
        }

        return droppedTableCount;
    }
   
   /**
    * Should insert an array of MenuItem into the database.
    * 
    * @return Number of rows inserted successfully.
    */
    public int insertMenuItems(MenuItem[] items){
        int addedMenuItemCount = 0;

        for(MenuItem item : items){
            try{
                addedMenuItemCount++;
                Statement statement = connection.createStatement();

                String query =  "INSERT INTO MenuItems " +
                                "VALUES (" +    
                                Integer.toString(item.getItemID()) + ", '" +
                                item.getItemName() + "', '" + 
                                item.getCuisine() + "', '" + 
                                Integer.toString(item.getPrice()) + 
                                "')";
                statement.executeUpdate(query);
            } catch(SQLException e) {
                addedMenuItemCount--;
                e.printStackTrace();
            }            
        }
        return addedMenuItemCount;
    }

   /**
    * Should insert an array of Ingredient into the database.
    *
    * @return Number of rows inserted successfully.
    */

    public int insertIngredients(Ingredient[] ingredients){
        int addedIngredientCount = 0;

        for(Ingredient ingredient : ingredients){
            try{
                addedIngredientCount++;
                Statement statement = connection.createStatement();

                String query =  "INSERT INTO Ingredients " +
                                "VALUES (" + 
                                Integer.toString(ingredient.getIngredientID()) + ", '" +
                                ingredient.getIngredientName() +
                                "')";
                statement.executeUpdate(query);
            } catch(SQLException e){
                addedIngredientCount--;
                e.printStackTrace();
            }
        }

        return addedIngredientCount;
    }

   /**
    * Should insert an array of Includes into the database.
    *
    * @return Number of rows inserted successfully.
    */
    public int insertIncludes(Includes[] includes){
	    int addedIncludeCount = 0;

        for(Includes include : includes){
    	    try{
               addedIncludeCount++;
               Statement statement = connection.createStatement();

               String query =  "INSERT INTO Includes " +
                               "VALUES (" + 
                               Integer.toString(include.getItemID()) + "," + 
                               Integer.toString(include.getIngredientID()) +
                               ")";
               
               statement.executeUpdate(query);
            } catch(SQLException e){
               addedIncludeCount--;
               e.printStackTrace();
            }
        }
       return addedIncludeCount;
    }
   
   /**
    * Should insert an array of DietaryCategory into the database.
    * 
    * @return Number of rows inserted successfully.
    */
    public int insertDietaryCategories(DietaryCategory[] categories) {
	   int addedCategoryCount = 0;
       
        for(DietaryCategory category : categories) {
            try {
               addedCategoryCount++;
               Statement statement = connection.createStatement();
               
               String query = 	"INSERT INTO DietaryCategories " + 
            		   			"VALUES (" +
            		   			Integer.toString(category.getIngredientID()) + ",'" +
            		   			category.getDietaryCategory() + 
            		   			"')";
               
               statement.executeUpdate(query);   
            }catch(SQLException e) {
        	   addedCategoryCount--;
               e.printStackTrace();
            }
        }
       
       return addedCategoryCount;
    }

   /**
    * Should insert an array of Seen into the database.
    * 
    * @return Number of rows inserted successfully.
    */

    public int insertRatings(Rating[] ratings) {
	   int addedRatingCount = 0;
       
        for(Rating rating : ratings) {
            try{
               addedRatingCount++;
               String query = 	"INSERT INTO Ratings(ratingID, itemID, rating, ratingDate)" +
                                "VALUES (?,?,?,?)";
               PreparedStatement statement = connection.prepareStatement(query);
               
               statement.setInt(1, rating.getRatingID());
               statement.setInt(2, rating.getItemID());
               statement.setInt(3, rating.getRating());
               
                if(rating.getRatingDate() != null) {
            	   java.util.Date date = (java.util.Date) new SimpleDateFormat("yyyy-MM-dd").parse(rating.getRatingDate());
                   java.sql.Date sqlD = new java.sql.Date(date.getTime());
                   statement.setDate(4, sqlD);

                }
               
               statement.execute();

            } catch(SQLException | ParseException e){
               addedRatingCount--;
               e.printStackTrace();
            }
        }
       
	   return addedRatingCount;
    }
   
   /**
    * Should return menu items that include the given ingredient
    * 
    * @return MenuItem[]
    */
    public MenuItem[] getMenuItemsWithGivenIngredient(String name) {
        List<MenuItem> result = new ArrayList <MenuItem>();

        try{
            String query =  "SELECT Menu.itemID, Menu.itemName, Menu.cuisine, Menu.price "+
                            "FROM Includes Inc, MenuItems Menu, Ingredients Ing "+
                            String.format("WHERE Ing.ingredientName = '%s' AND Inc.itemID = Menu.itemID AND Inc.ingredientID = Ing.ingredientID ",name)+
                            "ORDER BY  Menu.itemID ASC";

            Statement statement = connection.createStatement();
            ResultSet resultSet = statement.executeQuery(query);

            while(resultSet.next()){
                int itemID = resultSet.getInt("itemID");
                String itemName = resultSet.getString("itemName");
                String cuisine = resultSet.getString("cuisine");
                int price = resultSet.getInt("price");
                result.add(new MenuItem(itemID, itemName, cuisine, price)); 
            }
        }catch(SQLException e){
            e.printStackTrace();
        }
            
        return result.toArray(new MenuItem[0]);
    }

   /**
    * Should return menu items that do not have any ingredients in the Includes table
    *
    * @return MenuItem[]
    */
    public MenuItem[] getMenuItemsWithoutAnyIngredient() {
        List<MenuItem> result = new ArrayList <MenuItem>();

        try{
            String query =  "SELECT Menu.itemID, Menu.itemName, Menu.cuisine, Menu.price "+
                            "FROM MenuItems Menu "+
                            "WHERE Menu.itemID NOT IN (SELECT Inc.itemID FROM Includes Inc) "+
                            "ORDER BY Menu.itemID ASC";

            Statement statement = connection.createStatement();
            ResultSet resultSet = statement.executeQuery(query);

            while(resultSet.next()){
                int itemID = resultSet.getInt("itemID");
                String itemName = resultSet.getString("itemName");
                String cuisine = resultSet.getString("cuisine");
                int price = resultSet.getInt("price");
                result.add(new MenuItem(itemID, itemName, cuisine, price)); 
            }
        }catch(SQLException e){
            e.printStackTrace();
        }
            
        return result.toArray(new MenuItem[0]);
    }  

   /**
    * Should return ingredients that are not included in any menu item
    *
    * @return Ingredient[]
    */
    public Ingredient[] getNotIncludedIngredients(){
        List<Ingredient> result = new ArrayList<Ingredient>();

        try{
            String query =  "SELECT Ing.ingredientID, Ing.ingredientName "+
                            "FROM Ingredients Ing "+
                            "WHERE Ing.ingredientID NOT IN (SELECT Inc.ingredientID FROM Includes Inc) "+
                            "ORDER BY Ing.ingredientID ASC";

            Statement statement = connection.createStatement();
            ResultSet resultSet = statement.executeQuery(query);

            while(resultSet.next()){
                int ingredientID = resultSet.getInt("ingredientID");
                String ingredientName= resultSet.getString("ingredientName");
                result.add(new Ingredient(ingredientID,ingredientName)); 
            }
        }catch(SQLException e){
            e.printStackTrace();
        }

        return result.toArray(new Ingredient[0]);
    }


    /**
    * Should return menu item with the highest different ingredient number
    *
    * @return MenuItem
    */
    public MenuItem getMenuItemWithMostIngredients(){
        MenuItem result = null;

        try{
            String query =  "SELECT Menu.itemID, Menu.itemName, Menu.cuisine, Menu.price "+
                            "FROM MenuItems Menu , Includes Inc "+
                            "WHERE Menu.itemID = Inc.itemID "+
                            "GROUP BY Menu.itemID " +
                            "HAVING COUNT(*) = (SELECT MAX(IngCounts.counts) "+ 
                                "FROM (SELECT COUNT(*) as counts FROM MenuItems Menu1, Includes Inc1 "+ 
                                    "WHERE Menu1.itemID = Inc1.itemID GROUP BY Menu1.itemID) as IngCounts) " +
                            "ORDER BY Menu.itemID ASC";

            Statement statement = connection.createStatement();
            ResultSet resultSet = statement.executeQuery(query);

            resultSet.next();
            int itemID = resultSet.getInt("itemID");
            String itemName = resultSet.getString("itemName");
            String cuisine = resultSet.getString("cuisine");
            int price = resultSet.getInt("price");
            result = new MenuItem(itemID, itemName, cuisine, price); 
            
        }catch(SQLException e){
            e.printStackTrace();
        }
            
        return result;
    }


    /**
    * Should return menu items with their ID, name, and average rating
    *
    * @return MenuItemAverageRatingResult[]
    */
    public QueryResult.MenuItemAverageRatingResult[] getMenuItemsWithAvgRatings(){
        List<QueryResult.MenuItemAverageRatingResult> result = new ArrayList<QueryResult.MenuItemAverageRatingResult>();

        try{
            String query =  "SELECT Menu.itemID, Menu.itemName, AVG(Rat.rating) AS avgRating "+
                            "FROM MenuItems Menu LEFT OUTER JOIN Ratings Rat "+
                            "ON Rat.itemID = Menu.itemID " +
                            "GROUP BY Menu.itemID, Menu.itemName "+
            				"ORDER BY avgRating DESC";
            
            Statement statement = connection.createStatement();
            ResultSet resultSet = statement.executeQuery(query);

            while(resultSet.next()){
            	String itemID = resultSet.getString("itemID");
                String itemName = resultSet.getString("itemName");
                String avgRating = resultSet.getString("avgRating");

                result.add(new QueryResult.MenuItemAverageRatingResult(itemID, itemName, avgRating));
            }

        } catch(SQLException e){
            e.printStackTrace();
        }

        return result.toArray(new QueryResult.MenuItemAverageRatingResult[0]);
    }

    /**
    * Should return menu items that are suitable for a given dietary category
    *
    * @return MenuItem[]
    */
    public MenuItem[] getMenuItemsForDietaryCategory(String category){
        List<MenuItem> result = new ArrayList <MenuItem>();

        try{
            String query =  "SELECT DISTINCT  Menu.itemID, Menu.itemName, Menu.cuisine, Menu.price "+
                    "FROM MenuItems Menu, DietaryCategories Cat, Includes Inc "+ 
                    String.format("WHERE Cat.dietaryCategory =  '%s' AND  Menu.itemID = Inc.itemID AND Inc.ingredientID = Cat.ingredientID AND ",category)+
                    "Menu.itemID NOT IN "+
                        "(SELECT Menu1.itemID "+
                        "FROM MenuItems Menu1, Includes Inc1, "+
                            "(SELECT DISTINCT Inc2.ingredientID FROM Includes Inc2 "+
                            "WHERE Inc2.ingredientID NOT IN "+
                                "(SELECT DISTINCT Inc3.ingredientID FROM DietaryCategories Cat1, Includes Inc3  "+  
                                String.format("WHERE Cat1.DietaryCategory = '%s' AND Inc3.ingredientID = Cat1.ingredientID)) AS notInclude ",category)+
                        "WHERE Menu1.itemID = Inc1.itemID AND Inc1.ingredientID = notInclude.ingredientID) " + 
                    "ORDER BY Menu.itemID ASC";
            
            System.out.print(query);

            Statement statement = connection.createStatement();
            ResultSet resultSet = statement.executeQuery(query);

            while(resultSet.next()){
                int itemID = resultSet.getInt("itemID");
                String itemName = resultSet.getString("itemName");
                int price = resultSet.getInt("price");
                String cuisine = resultSet.getString("cuisine");
                result.add(new MenuItem(itemID, itemName, cuisine, price)); 
            }

        } catch(SQLException e){
            e.printStackTrace();
        }
        
        return result.toArray(new MenuItem[0]);
    }

    /**
    * Should return the most used ingredient across all menu items
    *
    * @return Ingredient
    */
    public Ingredient getMostUsedIngredient(){
        Ingredient result = null;

        try{
            String query =  "SELECT Ing.ingredientID, Ing.ingredientName "+
                            "FROM Ingredients Ing, Includes Inc "+
                            "WHERE Ing.ingredientID = Inc.ingredientID " +
                            "GROUP BY Ing.ingredientID  "+
                            "HAVING COUNT(*) = (SELECT MAX(IngCounts.counts) "+
                                "FROM (SELECT COUNT(*) as counts FROM Includes Inc "+ 
                                	"GROUP BY Inc.ingredientID) as IngCounts)";
            
            Statement statement = connection.createStatement();
            ResultSet resultSet = statement.executeQuery(query);

            resultSet.next();
            int ingredientID = resultSet.getInt("ingredientID");
            String ingredientName= resultSet.getString("ingredientName");
            result= new Ingredient(ingredientID,ingredientName); 
            
        }catch(SQLException e){
            e.printStackTrace();
        }
            
        return result;
    }


    /**
    * Should return cuisine names with their average ratings
    *
    * @return CuisineWithAverageResult[]
    */
    public QueryResult.CuisineWithAverageResult[] getCuisinesWithAvgRating(){
        List<QueryResult.CuisineWithAverageResult> result = new ArrayList<QueryResult.CuisineWithAverageResult>();

        try{
            String query =  "SELECT Menu.cuisine, AVG(Rat.rating) AS average " + 
                            "FROM MenuItems Menu LEFT OUTER JOIN Ratings Rat "+ 
                            "ON Menu.itemID = Rat.itemID "+
                            "GROUP BY Menu.cuisine "+
                            "ORDER BY average DESC ";

            Statement statement = connection.createStatement();
            ResultSet resultSet = statement.executeQuery(query);

            while(resultSet.next()){
            	String cuisineName = resultSet.getString("cuisine");
                String average = resultSet.getString("average");

                result.add(new QueryResult.CuisineWithAverageResult(cuisineName, average));
            }

        } catch(SQLException e){
            e.printStackTrace();
        }

        return result.toArray(new QueryResult.CuisineWithAverageResult[0]);
    }


    /**
    * Should return cuisine names with their average ingredient count per item
    *
    * @return CuisineWithAverageResult[]
    */
    public QueryResult.CuisineWithAverageResult[] getCuisinesWithAvgIngredientCount(){
    	List<QueryResult.CuisineWithAverageResult> result = new ArrayList<QueryResult.CuisineWithAverageResult>();

        try{
            String query =  "SELECT C.cuisine ,AVG(C.ingCount) AS average " +
                            "FROM (SELECT Menu1.cuisine, COUNT(Inc1.itemID) AS ingCount FROM MenuItems Menu1 LEFT OUTER JOIN Includes Inc1 ON Menu1.itemID = Inc1.itemID GROUP BY Menu1.itemID) AS C "+
                            "GROUP BY C.cuisine "+
                            "ORDER BY average DESC";

            Statement statement = connection.createStatement();
            ResultSet resultSet = statement.executeQuery(query);

            while(resultSet.next()){
            	String cuisineName = resultSet.getString("cuisine");
                String average = resultSet.getString("average");

                result.add(new QueryResult.CuisineWithAverageResult(cuisineName, average));
            }

        } catch(SQLException e){
            e.printStackTrace();
        }

        return result.toArray(new QueryResult.CuisineWithAverageResult[0]);
    }


    /**
    * Should increase the price of all menu items that include the given ingredient by the given amount
    *
    * @return the row count for SQL Data Manipulation Language (DML) statements
    */
    public int increasePrice(String ingredientName, String increaseAmount){
        int result = 0;
        
        try{
            String query =  "UPDATE MenuItems Menu " +
                            String.format("SET Menu.price = Menu.price + %s ", increaseAmount) +
                            "WHERE Menu.itemID IN " +  
                            "(SELECT Menu.itemID FROM Includes Inc, Ingredients Ing "+
                            String.format(" WHERE  Menu.itemID = Inc.itemID AND Ing.ingredientName  = '%s' AND Inc.ingredientID = Ing.ingredientID )",ingredientName )
                            ;

            PreparedStatement statement = connection.prepareStatement(query);
            result = statement.executeUpdate(); 
        } catch(SQLException e){
            e.printStackTrace();
        }

        return result;
    }

    /**
    * Should delete and return ratings that have an earlier rating date than the given date
    *
    * @return Rating[]
    */
    public Rating[] deleteOlderRatings(String date){
        List<Rating> result = new ArrayList<Rating>();
        
        try{    

            String query =  "SELECT Rat.ratingID, Rat.itemID, Rat.rating, Rat.ratingDate "+
                    "FROM Ratings Rat "+
                    String.format("WHERE Rat.ratingDate < DATE('%s')",date)+
                    "ORDER BY Rat.ratingID ASC";
            
            Statement statement = connection.createStatement();
            ResultSet resultSet = statement.executeQuery(query);
            
            while(resultSet.next()){
                int ratingID = resultSet.getInt("ratingID");
                int itemID = resultSet.getInt("itemID");
                int rating = resultSet.getInt("rating");
                String date1 = resultSet.getString("ratingDate");
                System.out.print("  "+ date1);
                result.add(new Rating(ratingID,itemID,rating,date1)); 
            
            } 
                
            String deleteQuery =	"DELETE FROM Ratings Rat "+
					String.format("WHERE Rat.ratingDate < DATE('%s')",date);

			PreparedStatement deleteStatement  = connection.prepareStatement(deleteQuery);
			deleteStatement.executeUpdate();
				
        }catch(SQLException e){
            e.printStackTrace();
        }

        return result.toArray(new Rating[0]);
    }

}
