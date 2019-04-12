using System.Collections;
using System.Collections.Generic;
using UnityEngine;


public class DoorSwitch : MonoBehaviour {


    [SerializeField]
    public GameObject Door;
    public GameObject Player;
	// Use this for initialization
	void Start ()
    {
		
	}
	
	// Update is called once per frame
	void Update ()
    {
        
	}
    public void OnCollisionEnter2D(Collision2D other)
    {
        Debug.Log("Collision detected. Attempting to compare tag.");
        if(Player.CompareTag("Player"))
        {
            Debug.Log("Player tag compared. Broadcasting.");
            Door.BroadcastMessage("OpenDoor");
            Debug.Log("Message Broadcast.");
        
        }
    }
}
