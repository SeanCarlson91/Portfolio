using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;


public class Health : MonoBehaviour {

    public Text deathUI;
    public const int maxHealth = 100;
	public int currentHealth = maxHealth;
	public RectTransform healthBar;

    private void Start()
    {
        deathUI.enabled = false;
    }


    public void TakeDamage(int amount)
	{
		currentHealth -= amount;
		if (currentHealth <= 0)
		{
			currentHealth = 0;
			Debug.Log("Dead!");
            CharacterController m_CharacterController = GetComponent<CharacterController>();
            m_CharacterController.enabled = false;
            deathUI.enabled = true;
            Invoke("Death", 2.0f);
		}

		healthBar.sizeDelta = new Vector2(currentHealth, healthBar.sizeDelta.y);
	}

    void Death()
    {
        SceneManager.LoadScene(SceneManager.GetActiveScene().buildIndex);
    }
}