using UnityEngine;
using System.Collections;

public class Respawn : MonoBehaviour {

	public Transform destination;
	public Transform player;

	void OnTriggerEnter2D (Collider2D other)
	{
		if (other.tag == "Player"){
			KillPlayer ();
		}
	}

	void KillPlayer () {
		player.transform.position = destination.transform.position;
	}
}
