using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;
using System.Collections;

public class LevelEnd : MonoBehaviour {

	public Canvas proceedCanvas;
	public Button nextLevel;
	public int nextScene;

	void Start()
	{
        Debug.Log("Initialized end level.");
		proceedCanvas.enabled = false;
		nextLevel.enabled = false;
	}


	void OnTriggerEnter2D (Collider2D other)
	{
        
        if (other.tag == "Player") {
			Destroy (other.gameObject);
			EnableUI ();
		}
	}

	void EnableUI ()
	{
        Debug.Log("GUI Enabled.");
        proceedCanvas.enabled = true;
		nextLevel.enabled = true;
	}

	public void NextLevel ()
	{
        Debug.Log("Loading scene.");
        SceneManager.LoadScene (nextScene, LoadSceneMode.Single);
	}
}

