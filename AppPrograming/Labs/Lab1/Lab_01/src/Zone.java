/**
 * @author Abit Gurung (jkd175)
 * THis class adds animals to respective zones
 */
public class Zone {

	private String name;
	private Animal[] animals;
	private int count;

	Zone(String name, int animalsize)
	{
		this.name = name;
		animals = new Animal[animalsize];
		count = 0;
	}
	void addAnimal(Animal animal)
	{
		if(count < animals.length)
		{
			animals[count] = animal;
			count++;
		}
	}
	public Animal[] getAnimals()
	{
		return animals;
	}
	public void setCount(int count)
	{
		this.count = count;
	}
	public int getAnimalsCnt()
	{
		return count;
	}
	public void setAnimals(Animal[] animals)
	{
		this.animals = animals;
	}
	public String getName()
	{
		return name;
	}
	public String toString()
	{
		StringBuilder data = new StringBuilder(name  + " Zone : ");
		data.append("\n").append("-".repeat(Math.max(0, data.length()-1)));
		for(int j = 0; j < count; j++)
		{
			data.append("\n").append(animals[j]);
		}
		return data.toString();
	}
}
