using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class ResetController : MonoBehaviour
{
	void Update ()
    {
        GetRInput(SceneManager.LoadScene);
	}

    // Yeah, it's overdesigned, but I'm having a good time playing
    // around with Actions and trying to be fancy.
    private bool GetRInput(System.Action<int> effect)
    {
        if (Input.GetKeyDown(KeyCode.R))
        {
            effect(SceneManager.GetActiveScene().buildIndex);
            return true;
        }

        return false;
    }
}
