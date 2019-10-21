
/**
 * @author Abit Gurung (jkd175)
 * This class collects the animals names and types
 */
public class Animal {

   private String name;
   private String type;
   private boolean isCarnivore;

   public Animal(String name, String type, boolean isCarnivore) {
      this.name = name;
      this.type = type;
      this.isCarnivore = isCarnivore;
   }

   public String getName() {
      return name;
   }

   public String getType() {
      return type;
   }

   public boolean isCarnivore() {
      return isCarnivore;
   }

   public String toString() {
      return " >>  " + name + " - " + type + (isCarnivore() ? " (Carnivore)" : " (Vegetarian)");
   }
}
