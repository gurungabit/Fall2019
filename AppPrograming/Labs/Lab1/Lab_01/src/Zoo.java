/**
 * This class adds zones in the zoo
 */

/**
 * @author Abit Gurung (jkd175)
 *
 */
public class Zoo {

   private String name;
   private Zone[] zones;
   private int zoneCnt;

   Zoo(String name, int size) {
      this.name = name;
      zones = new Zone[size];
      zoneCnt = 0;
   }

   void addZone(Zone zone) {
      if (zoneCnt < zones.length) {
         zones[zoneCnt] = zone;

         zoneCnt++;
      }
   }

   // getter for the zoo names
   public String getName() {
      return name;
   }

   // count number of zones
   public int getZoneCnt() {
      return zoneCnt;
   }

   public Zone[] getZones() {
      return zones;
   }

   // setter for zone
   public void setZones(Zone[] zones) {
      this.zones = zones;
   }

   public String toString() {
      StringBuilder data = new StringBuilder("Welcome to " + "\"" + name + "\"" + "!\n");

      data.append("-".repeat(Math.max(0, data.length() - 1)));
      for (int j = 0; j < zoneCnt; j++) {
         data.append("\n").append(zones[j]);
      }
      return data.toString();
   }
}
