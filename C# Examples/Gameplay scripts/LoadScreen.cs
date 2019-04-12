using System.Collections;
using System.Collections.Generic;
using UnityEngine.SceneManagement;
using UnityEngine;

public class LoadScreen : MonoBehaviour {
	public void StartGame()
	{
		SceneManager.LoadScene (1);
	}

	public void StartCredits()
	{
		SceneManager.LoadScene (2);
	}

	public void loadStartScreen()
	{
		SceneManager.LoadScene (0);
	}
}
