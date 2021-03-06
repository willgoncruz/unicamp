package card;

public class MinionCard {

	private int id;
	private int attack;
	private int manaCost;
	private int totalHealth;
	private int currentHealth;

	// Note: ;-; (Sad face)
	public String name;

	public MinionCard(int id, String name, int manaCost) {
		this.id = id;
		this.name = name;
		this.manaCost = manaCost;
	}

	public MinionCard(MinionCard other) {
		this.id = other.getId();
		this.name = other.getName();
		this.attack = other.getAttack();
		this.manaCost = other.getManaCost();
		this.currentHealth = other.getCurrentHealth();
		this.totalHealth = other.getTotalHealth();
	}

	public MinionCard(int id, String name, int attack, int currentHealth, int totalHealth, int manaCost) {
		this.id = id;
		this.name = name;
		this.attack = attack;
		this.currentHealth = currentHealth;
		this.totalHealth = totalHealth;
		this.manaCost = manaCost;
	}

	public void buff(int attackAndHealthBuff) {
		this.buff(attackAndHealthBuff, attackAndHealthBuff);
	}

	public void buff(int attackBuff, int healthBuff) {
		int oldAttack = this.attack;
		int oldHealth = this.currentHealth;

		if (attackBuff > 0) {
			this.attack += attackBuff;
		}

		if (healthBuff > 0) {
			this.currentHealth += healthBuff;
		}

		if (this.hasAppliedBuff(oldAttack, oldHealth)) {
			this.buffedName();
		}
	}

	private boolean hasAppliedBuff(int oldAttack, int oldHealth) {
		return (oldAttack < this.attack || oldHealth < this.currentHealth);
	}

	private void buffedName() {
		this.name += " Buffed";
	}

	public int getId() {
		return id;
	}

	public void setId(int id) {
		this.id = id;
	}

	public String getName() {
		return name;
	}

	public void setName(String name) {
		this.name = name;
	}

	public int getAttack() {
		return attack;
	}

	public void setAttack(int attack) {
		this.attack = attack;
	}

	public int getCurrentHealth() {
		return currentHealth;
	}

	public void setCurrentHealth(int currentHealth) {
		this.currentHealth = currentHealth;
	}

	public int getTotalHealth() {
		return totalHealth;
	}

	public void setTotalHealth(int totalHealth) {
		this.totalHealth = totalHealth;
	}

	public int getManaCost() {
		return manaCost;
	}

	public void setManaCost(int manaCost) {
		this.manaCost = manaCost;
	}

	@Override
	public String toString() {
		String out = this.name + " (ID: " + this.id + ")\n";
		out += "Ataque = " + this.attack + "\n";
		out += "Vida Atual = " + this.currentHealth + "\n";
		out += "Vida Maxima = " + this.totalHealth + "\n";
		out += "Custo de Mana = " + this.manaCost + "\n";
		return out;
	}

}
